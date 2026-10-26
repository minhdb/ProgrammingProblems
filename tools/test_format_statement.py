"""Regression tests for pasted statements and exact preservation of code/data."""

import ast
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

from format_statement import FormatError, format_source


class StatementTests(unittest.TestCase):
    def test_cpp_html_paste(self):
        code = '\n#include <iostream>\nint main() { std::cout << "/* intact */"; }\n'
        source = '/**\n * Milk\n * https://example.org/milk\n\n' + (
            'The first line contains N\n integers (1≤N≤100\n), and each value a\n, b\n, and g\n is positive and a≠b\n.\n'
            'SAMPLE INPUT:\n10 3\n11 4\n12 5\nSAMPLE OUTPUT:\n0\n10\n2\n'
            'In this example, the total amount of milk stays the same.\n*/'
        ) + code
        result = format_source(source, 'milk.cpp', 60)
        self.assertTrue(result.endswith(code))
        self.assertIn('(1≤N≤100),', result)
        self.assertIn('a, b, and g', result)
        self.assertIn('a≠b.', result)
        self.assertIn(' * 10 3\n * 11 4\n * 12 5\n', result)
        self.assertIn(' * 0\n * 10\n * 2\n', result)
        self.assertTrue(all(len(row) <= 60 for row in result.split('*/')[0].splitlines()))
        self.assertEqual(result, format_source(result, 'milk.cpp', 60))

    def test_textual_samples_and_blank_lines(self):
        sample = 'Hello world!\nA second line of output\n\n  indented\n'
        result = format_source('/*\nSAMPLE OUTPUT:\n' + sample + '*/\nint x;', 'x.cpp')
        self.assertIn(' * Hello world!\n * A second line of output\n *\n *   indented', result)

    def test_fenced_diagram_and_aligned_rows(self):
        source = '/*\nDiagram:\n```\n  a\n / \\\nb   c\n```\n\nInitial State: 3  4  5\n*/\nint x;'
        result = format_source(source, 'x.cpp')
        self.assertIn(' *   a\n *  / \\\n * b   c', result)
        self.assertIn(' * Initial State: 3  4  5', result)
        self.assertEqual(result, format_source(result, 'x.cpp'))

    def test_usaco_metadata_is_untouched(self):
        metadata = '/*\nID: minh\nLANG: C++11\nTASK: test\n*/\n\n'
        result = format_source(metadata + '/* A problem.\nMore details.\n*/\nint x;', 'x.cpp')
        self.assertTrue(result.startswith(metadata))
        self.assertIn(' * A problem. More details.', result)
        self.assertEqual(metadata + 'int x;', format_source(metadata + 'int x;', 'x.cpp'))

    def test_python_docstring_and_incomplete_solution(self):
        prefix = '#!/usr/bin/env python3\n# coding: utf-8\n'
        code = '\nfor x in []:\n'
        source = prefix + "'''Title\n\n" + ('This is some explanatory prose. ' * 8) + "\n'''" + code
        result = format_source(source, 'x.py', 55)
        self.assertTrue(result.startswith(prefix))
        self.assertTrue(result.endswith(code))
        self.assertEqual(result, format_source(result, 'x.py', 55))

    def test_python_ast_except_documentation(self):
        source = '"""Title\n\n' + ('A sentence to wrap. ' * 10) + '\n"""\nvalue = "# unchanged"\n'
        before, after = ast.parse(source), ast.parse(format_source(source, 'x.py', 50))
        before.body[0].value.value = after.body[0].value.value = ''
        self.assertEqual(ast.dump(before), ast.dump(after))

    def test_raw_python_and_escape_sequences(self):
        source = 'r"""Example\n\nSAMPLE INPUT:\na\\nb\n"""\nvalue = "x"\n'
        result = format_source(source, 'x.py')
        self.assertIn('a\\nb', result)
        self.assertTrue(result.startswith('r"""'))
        self.assertEqual(result, format_source(result, 'x.py'))

    def test_python_string_expression_is_untouched(self):
        for source in ['x = """not docs"""\n', '"""left""" + "right"\n', '"""left""" "right"\n']:
            self.assertEqual(source, format_source(source, 'x.py'))

    def test_line_comments(self):
        source = '//Title\n//\n//' + ('A sentence to wrap. ' * 6) + '\nint x;\n'
        result = format_source(source, 'x.cpp', 50)
        self.assertTrue(result.startswith('// Title\n//\n'))
        self.assertTrue(result.endswith('int x;\n'))
        self.assertEqual(result, format_source(result, 'x.cpp', 50))

    def test_bom_crlf_and_no_final_newline(self):
        for name, source in [('x.cpp', '\ufeff/*\r\nA title\r\n*/\r\nint x;'),
                             ('x.py', '\ufeff"""\r\nA title\r\n"""\r\nx = 1')]:
            result = format_source(source, name)
            self.assertTrue(result.startswith('\ufeff'))
            self.assertNotIn('\n', result.replace('\r\n', ''))
            self.assertFalse(result.endswith('\n'))

    def test_missing_or_unterminated_header(self):
        for name, source in [('x.cpp', 'int x; // explanation\n'), ('x.py', 'x = 1\n')]:
            self.assertEqual(source, format_source(source, name))
        for name, source in [('x.cpp', '/* unfinished'), ('x.py', '"""unfinished')]:
            with self.assertRaises(FormatError):
                format_source(source, name)

    def test_cli_preview_write_check_and_stdin(self):
        tool = str(Path(__file__).with_name('format_statement.py'))
        with tempfile.TemporaryDirectory() as folder:
            path = Path(folder) / 'a.cpp'
            source = b'/* Hello\nworld\n*/\nint x;\n'
            path.write_bytes(source)
            def run(*args, **kwargs):
                return subprocess.run([sys.executable, tool, *args], capture_output=True, **kwargs)
            preview = run(str(path))
            self.assertEqual(preview.returncode, 0)
            self.assertIn(b'+ * Hello world', preview.stdout)
            self.assertEqual(source, path.read_bytes())
            self.assertEqual(run('--check', str(path)).returncode, 1)
            self.assertEqual(run('--write', str(path)).returncode, 0)
            self.assertEqual(run('--check', str(path)).returncode, 0)
            filtered = run('--stdin-filename', 'a.cpp', input=source)
            self.assertEqual(filtered.returncode, 0)
            self.assertEqual(filtered.stdout, path.read_bytes())
            broken = run('--stdin-filename', 'a.cpp', input=b'/* unfinished')
            self.assertEqual(broken.returncode, 2)
            self.assertEqual(broken.stdout, b'/* unfinished')


if __name__ == '__main__':
    unittest.main()
