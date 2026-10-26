#!/usr/bin/env python3
"""Reflow a leading C/C++ problem comment or Python module docstring.

Uses only the Python standard library. Defaults to a diff preview; --write
updates files, and --stdin-filename supports editor buffer filters.
"""

import argparse
import difflib
import io
from pathlib import Path
import re
import sys
import textwrap
import tokenize


CPP_SUFFIXES = {'.c', '.cc', '.cpp', '.cxx', '.h', '.hpp', '.hxx'}
HEADING = re.compile(
    r'^(?:(?:sample\s+)?(?:input|output)(?:\s+(?:format|sample|example))?'
    r'(?:\s+\d+)?(?:\s*\([^\n]*\))?|examples?(?:\s+\d+)?|'
    r'explanation|notes?|constraints|scoring|problem statement)\s*:?$', re.I
)
SAMPLE = re.compile(r'^(?:sample\s+(?:input|output)|(?:input|output)\s+(?:sample|example)|examples?)', re.I)
EXPLANATION = re.compile(r'^(?:In this example\b|Explanation\s*:|Note\s*:)', re.I)
URL = re.compile(r'^https?://\S+$')
LIST_ITEM = re.compile(r'^\s*(?:[-+*]|\d+[.)])\s+')


class FormatError(ValueError):
    """Input cannot be formatted without guessing its comment boundary."""


def trim_blank_edges(rows):
    rows = list(rows)
    while rows and not rows[0].strip():
        rows.pop(0)
    while rows and not rows[-1].strip():
        rows.pop()
    return rows


def reflow(rows, width):
    """Wrap prose; keep samples, fences, lists, and visibly aligned data intact."""
    result, paragraph = [], []
    sample = False
    fence = None

    def flush():
        if paragraph:
            text = ' '.join(part.strip() for part in paragraph)
            # Copied HTML math often places commas and parentheses on new lines.
            text = re.sub(r'\s+([,;:)]|\.(?!\.))', r'\1', text)
            result.extend(textwrap.wrap(text, width=width, break_long_words=False,
                                        break_on_hyphens=False))
            paragraph.clear()

    for row in trim_blank_edges(rows):
        stripped = row.strip()
        fence_match = re.match(r'^(`{3,}|~{3,})', stripped)
        if fence is not None:
            result.append(row)
            if fence_match and fence_match.group(1).startswith(fence):
                fence = None
            continue
        if fence_match:
            flush()
            fence = fence_match.group(1)
            result.append(row)
        elif HEADING.fullmatch(stripped):
            flush()
            if result and result[-1]:
                result.append('')
            result.append(stripped)
            sample = bool(SAMPLE.match(stripped))
        elif sample and not EXPLANATION.match(stripped):
            # Even blank lines and prose-looking sample output are significant.
            result.append(row)
        else:
            if sample:
                if result and result[-1]:
                    result.append('')
                sample = False
            if not stripped:
                flush()
                result.append('')
            elif URL.fullmatch(stripped):
                flush()
                result.append(stripped)
            elif (LIST_ITEM.match(row)
                  or re.search(r'\S[ \t]{2,}\S', row)
                  or (re.fullmatch(r'[\d\s.,+*/=<>|_#\\-]+', stripped)
                      and re.search(r'[\d/=<>|_#\\]', stripped))
                  or stripped.startswith(('Input:', 'Output:', '>>>', '...'))):
                flush()
                result.append(row.rstrip())
            else:
                paragraph.append(row)
    flush()
    return result


def cpp_body(raw):
    """Remove a conventional star margin without stripping unprefixed grids."""
    rows = raw.splitlines()
    result = []
    for row in rows:
        if re.match(r'^ \*(?: |$)', row):
            result.append(row[3:] if row.startswith(' * ') else '')
        else:
            result.append(row)
    return trim_blank_edges(result)


def cpp_header(text, width):
    pos = len(text) - len(text.lstrip())
    while text.startswith(('/*', '//'), pos):
        if text.startswith('/*', pos):
            end = text.find('*/', pos + 2)
            if end < 0:
                raise FormatError('close the opening comment with */ before formatting')
            end += 2
            opener = '/**' if text.startswith('/**', pos) else ('/*!' if text.startswith('/*!', pos) else '/*')
            rows = cpp_body(text[pos + len(opener):end - 2])
            # USACO training headers have a separate, machine-readable layout.
            body = '\n'.join(rows)
            if re.search(r'^\s*ID:', body, re.M) and re.search(r'^\s*LANG:', body, re.M):
                pos = end + len(text[end:]) - len(text[end:].lstrip())
                continue
            lines = reflow(rows, width - 3)
            newline = '\r\n' if '\r\n' in text[pos:end] else '\n'
            formatted = opener + newline
            formatted += ''.join(' *' + (' ' + row if row else '') + newline for row in lines)
            formatted += ' */'
            return text[:pos] + formatted + text[end:]
        else:
            match = re.match(r'(?://[^\r\n]*(?:\r?\n|$))+', text[pos:])
            raw = match.group()
            rows = [re.sub(r'^// ?', '', row) for row in raw.splitlines()]
            newline = '\r\n' if '\r\n' in raw else '\n'
            lines = reflow(rows, width - 3)
            formatted = newline.join('// ' + row if row else '//' for row in lines)
            if raw.endswith('\n'):
                formatted += newline
            return text[:pos] + formatted + text[pos + len(raw):]
    return text


def python_header(text, width):
    # Read only the first statement: unfinished solution code is allowed.
    stream = tokenize.generate_tokens(io.StringIO(text).readline)
    try:
        first = next((t for t in stream
                      if t.type not in {tokenize.COMMENT, tokenize.NL, tokenize.NEWLINE}), None)
        if first is None or first.type != tokenize.STRING or first.start[1] != 0:
            return text
        match = re.match(r'(?i)(r?)("""|\x27\x27\x27)', first.string)
        if not match:
            return text
        following = next(stream)
        if following.type not in {tokenize.NEWLINE, tokenize.ENDMARKER}:
            return text  # A string expression, rather than a standalone docstring.
    except (tokenize.TokenError, IndentationError) as error:
        raise FormatError(f'cannot read the opening docstring: {error.args[0]}') from error

    prefix, quote = match.groups()
    body = first.string[len(prefix) + 3:-3]
    # Keep escape sequences literal; evaluating/requoting could change examples.
    rows = reflow(body.splitlines(), width - len(prefix) - 3)
    if not rows:
        return text
    newline = '\r\n' if '\r\n' in first.string else '\n'
    if len(rows) == 1 and len(rows[0]) + len(prefix) + 6 <= width:
        formatted = prefix + quote + rows[0] + quote
    else:
        if len(rows) > 1 and rows[1] and URL.fullmatch(rows[1]):
            rows.insert(1, '')
        formatted = prefix + quote + newline.join(rows) + newline + quote
    lines = text.splitlines(keepends=True)
    start = sum(map(len, lines[:first.start[0] - 1])) + first.start[1]
    end = sum(map(len, lines[:first.end[0] - 1])) + first.end[1]
    return text[:start] + formatted + text[end:]


def format_source(text, filename, width=79):
    suffix = Path(filename).suffix.lower()
    if width < 20:
        raise FormatError('width must be at least 20')
    bom = '\ufeff' if text.startswith('\ufeff') else ''
    body = text[len(bom):]
    if suffix in CPP_SUFFIXES:
        return bom + cpp_header(body, width)
    if suffix == '.py':
        return bom + python_header(body, width)
    raise FormatError(f'unsupported extension: {suffix or "(none)"}')


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('files', nargs='*', type=Path)
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument('--write', action='store_true', help='update the named files')
    mode.add_argument('--check', action='store_true', help='exit 1 if formatting is needed')
    parser.add_argument('--width', type=int, default=79, help='line width including comment markers (default: 79)')
    parser.add_argument('--stdin-filename', help='read a buffer from stdin and use this filename to select the language')
    args = parser.parse_args(argv)
    if args.stdin_filename:
        if args.files or args.write or args.check:
            parser.error('--stdin-filename cannot be combined with files, --write, or --check')
        data = sys.stdin.buffer.read()
        try:
            output = format_source(data.decode('utf-8'), args.stdin_filename, args.width).encode('utf-8')
        except (FormatError, UnicodeError) as error:
            sys.stdout.buffer.write(data)  # Leave editor contents available on failure.
            print(f'format_statement: {error}', file=sys.stderr)
            return 2
        sys.stdout.buffer.write(output)
        return 0
    if not args.files:
        parser.error('provide files or --stdin-filename')

    changes = []
    try:
        for path in dict.fromkeys(args.files):
            if path.is_symlink():
                raise FormatError(f'{path}: use the real path instead of a symlink')
            original = path.read_bytes()
            updated = format_source(original.decode('utf-8'), path, args.width).encode('utf-8')
            if updated != original:
                changes.append((path, original, updated))
        for path, original, updated in changes:
            if args.write:
                if path.read_bytes() != original:
                    raise FormatError(f'{path}: file changed while formatting; retry')
                path.write_bytes(updated)
                print(f'Formatted {path}')
            elif args.check:
                print(f'Needs formatting: {path}')
            else:
                sys.stdout.writelines(difflib.unified_diff(
                    original.decode('utf-8').splitlines(keepends=True),
                    updated.decode('utf-8').splitlines(keepends=True),
                    fromfile=str(path), tofile=str(path) + ' (formatted)',
                ))
    except (OSError, UnicodeError, FormatError) as error:
        print(f'format_statement: {error}', file=sys.stderr)
        return 2
    if not changes:
        print('No formatting changes needed.')
    return 1 if args.check and changes else 0


if __name__ == '__main__':
    sys.exit(main())
