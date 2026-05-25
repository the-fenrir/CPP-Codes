# 28.6 — Basic file I/O

> learncpp.com: https://www.learncpp.com/cpp-tutorial/basic-file-io/

## Why it matters
A program that can only talk to the terminal isn't very useful. File I/O is the same `<<`/`>>` you already know, pointed at a file. The new vocabulary is small: three classes, half a dozen open modes, and one critical habit (RAII — let the destructor close the file).

## Key points
- Header `<fstream>`. Three classes:
  - `std::ifstream` — read   (`: istream`)
  - `std::ofstream` — write  (`: ostream`)
  - `std::fstream`  — both   (`: iostream`)
- **Opening:** pass a path to the constructor. The file opens immediately:
  ```cpp
  std::ofstream out{ "data.txt" };       // truncates by default
  if (!out) { /* failed — disk full, no permission, ... */ }
  ```
- **Open modes** (bitmask, header `<ios>`):
  - `std::ios::in`     — read (ifstream default)
  - `std::ios::out`    — write (ofstream default; **truncates** unless combined with `app`)
  - `std::ios::app`    — append: every write goes to end
  - `std::ios::ate`    — open *at* end, but writes go wherever you seek
  - `std::ios::trunc`  — erase existing contents
  - `std::ios::binary` — don't translate `'\n'`; treat file as raw bytes
- **Closing:** RAII closes on destruction. Explicit `close()` only when you need to reopen with `open(...)`.
- **Reading line-by-line:** `while (std::getline(in, line))` is the idiom. Plain `>>` breaks on every whitespace.
- **Buffering:** writes are buffered; the destructor flushes. For long-running writers, call `flush()` (or use `std::endl` if you don't mind the cost) at meaningful sync points.

## Code in this folder
- `main.cpp` — writes a small text file, reads it back two ways (line-oriented and token-oriented), demonstrates append mode and the error-checking pattern.
- Output goes to `std::filesystem::temp_directory_path() / "cpp28_06_demo.txt"` and is deleted at the end — no pollution in the source tree.

## Gotchas
- **Default `ofstream` open truncates.** If you want to append, you must pass `std::ios::app`. This eats more files than any other I/O mistake.
- **Path is relative to the *current working directory*, not the source file.** Use `std::filesystem::current_path()` if you're confused.
- **Don't check `!file.is_open()` *after* using the stream** — by then you've already read garbage. Check immediately after construction or after `open()`.
- Text mode on Windows translates `'\n'` to `"\r\n"` on write. Mostly invisible — until you seek by byte offset (lesson 28.7).

## Run
    make 28.06
