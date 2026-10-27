# ProgrammingProblems

Programming/Tech interview problems I have tackled in the past few years.

## C/C++ file naming standard

This repo mixes judge submissions and personal practice code, so file extensions follow the *source* of the problem rather than one blanket rule:

| Extension | Use it for |
|---|---|
| `.cpp` | Online-judge submissions: `CodeForces/`, `TopCoder/`, `USACO/`, `UVA/`, `SPOJ/`. Matches the convention expected by those judges/graders. |
| `.cc` | Personal/book-driven solution files that are not judge submissions: `EPI/`, `the-daily-byte/`, `misc/`. Matches Google's C++ style guide, which this repo otherwise follows loosely. |
| `.hpp` | Headers containing template classes/structs meant to be `#include`d elsewhere, with no matching `.cc`/`.cpp` (e.g. `EPI/data_structures/*.hpp`). Templates must be fully defined in the header (no separate-compilation `.cpp`), so header-only is the correct, not just conventional, choice here. |
| `.h` | Same role as `.hpp` (paired declaration header for a `.cc` file, e.g. `the-daily-byte/data_structures/singly_linked_node.h` + `.cc`), or a header containing only templates. Prefer `.hpp` for new template-only headers to make "C++-only, no matching .cpp" explicit; `.h` stays fine when it's genuinely paired with a `.cc`. |

New files should follow whichever column matches where they live; don't mix `.cpp` into `EPI`/`the-daily-byte`/`misc`, or `.cc` into a judge folder.

## C/C++ best practices for this repo

- **Templates are header-only.** A generic container/data structure (anything with `template <typename T>`) must live entirely in a `.hpp`/`.h` — the definition has to be visible at every instantiation point. Don't try to split a template into a `.hpp` declaration + `.cpp` definition.
- **No `using` declarations at header scope.** `using std::shared_ptr;` etc. at the top of a header leaks into every translation unit that includes it. Qualify with `std::` at the point of use instead (`std::shared_ptr<T>`, `std::vector<T>`, ...). `using` is fine inside a `.cc`/`.cpp` implementation file, just not in a shared header.
- **Use `weak_ptr` for back/parent pointers.** A node that holds a `shared_ptr` down to its children *and* a `shared_ptr` back up to its parent creates a reference cycle that never gets freed. Parent/back-pointers should be `std::weak_ptr`, locked (`.lock()`) at the point of use.
- **Use `#ifndef`/`#define`/`#endif` include guards, not `#pragma once`.** `#pragma once` is a widely-supported compiler extension, but it is not part of the ISO C++ standard; include guards are portable to any conforming compiler. This also matches Google's C++ style guide, which this repo loosely follows for `.cc` files. Guard macro names follow `<FILE>_<EXT>_`, e.g. `BINARY_TREE_HPP_`.
- **C++20 modules exist but aren't the default here.** `import`/`export module` can replace headers (including for templates), but toolchain/build support is still inconsistent across compilers and CMake versions as of 2026. Stick with header-only `.hpp` for data structures in this repo rather than introducing modules piecemeal.

## Repository utilities

- [`tools/challenge`](tools/challenge) prints a starter C++ solution. From the
  repository root, run `bash tools/challenge > solution.cpp` to create a file.
- [`tools/cleanup.py`](tools/cleanup.py) is an unfinished utility for organizing
  solutions by judge and language. It currently has an incomplete loop and
  cannot run.

## Formatting pasted problem statements

Paste the statement inside a closed opening C/C++ comment (`/* ... */`,
`/** ... */`, or consecutive `//` lines) or a Python module docstring
(`"""..."""` or triple single quotes). Then run this from the repository root:

```sh
tools/format-statement USACO/C-C++/bronze/mixing_milk.cpp
tools/format-statement USACO/Python/bronze/shell_game.py
```

Save the file before running the shell command. The wrapper updates files by
default. Put `--preview` first to preview a diff, or `--check` first to report
files that need formatting without editing them. Use `--width 100` to change
the default 79-character width. Multiple filenames are accepted; quote paths
that contain spaces. The wrapper finds its companion Python script relative
to itself, and interprets input paths relative to your current directory.

For a short command from any directory, add this alias to your shell config
(using the path to your checkout), or run it in your current shell:

```sh
alias format-statement='/home/minhdb/workspaces/ProgrammingProblems/tools/format-statement'
format-statement mixing_milk.cpp
format-statement --preview shell_game.py
```

The underlying command, `python3 tools/format_statement.py --write FILE`, also
remains available. The formatter uses only the Python standard library and
changes the leading statement; code and later comments remain byte-for-byte
intact. It skips USACO `ID`/`LANG` submission headers. After formatting a saved
file from the shell, use `:e` in Vim/Neovim to reload it.

The formatter recognizes headings such as `INPUT FORMAT`, `SAMPLE INPUT`,
`SAMPLE OUTPUT`, and `Explanation`. It wraps prose and joins broken lines from
copied HTML math. Sample sections retain their line breaks and spacing until
the next heading or an `In this example` explanation. Put unusual examples,
diagrams, or other text whose spacing matters inside triple-backtick fenced
blocks within the comment. Sample lines, tables, URLs, and long unbroken words
may exceed the requested width. This is a text formatter, so it cannot reconstruct
math symbols or layout that the browser did not copy.

On this machine, **F4** formats the opening problem statement in C/C++ and
Python buffers in both Vim and Neovim, including unsaved edits. It works from
any directory and uses the buffer's filetype, so unnamed buffers work after
`:setfiletype cpp` or `:setfiletype python`. Use `u` to undo or `:w` to save;
F5 continues to save and compile C++. `:StatementFormat` runs the same action.

The shared mapping lives in `~/.vim/after/plugin/statement-format.vim` and uses
Python 3 plus `~/.local/share/format-statement/format_statement.py`. The installed
formatter is a copy of this repository's script, so moving this checkout does
not break F4. Future script updates need to be copied to that installed path.
Restart the editor or run `:source ~/.vim/after/plugin/statement-format.vim`
to enable the new mapping in an existing session.

Without the installed mapping, this command formats the current buffer,
including unsaved changes (use the path to your checkout):

```vim
:execute '%!python3 /home/minhdb/workspaces/ProgrammingProblems/tools/format_statement.py --stdin-filename ' . shellescape(expand('%:p'))
```

Run the formatter's regression tests with:

```sh
python3 -B -m unittest discover -s tools -p 'test_format_statement.py'
```
