# 28.7 — Random file I/O

> learncpp.com: https://www.learncpp.com/cpp-tutorial/random-file-io/

## Why it matters
Sequential reading is fine for logs and config files, but databases, save games, archive formats, and any "fixed-record" file need to jump to byte N and read/write there. That's `seekg`/`seekp` + `tellg`/`tellp`. The same operations also unlock one common trick: compute a file's size by seeking to end and reading the position.

## Key points
- **Seek functions:**
  - `seekg(off)` / `seekg(off, dir)` — set the *read* (get) position.
  - `seekp(off)` / `seekp(off, dir)` — set the *write* (put) position.
  - For file streams the two pointers move together, so either works on `fstream`.
- **Direction flags** (in `std::ios`):
  - `std::ios::beg` — from start (default)
  - `std::ios::cur` — from current position
  - `std::ios::end` — from end (use negative offsets)
- **Tell functions:** `tellg()` / `tellp()` return the current absolute position (`std::streampos`, convertible to integer).
- **File size idiom:**
  ```cpp
  in.seekg(0, std::ios::end);
  auto sz = in.tellg();
  in.seekg(0, std::ios::beg);
  ```
- **Read+write `fstream`:** open with `std::ios::in | std::ios::out`. You can't switch between reading and writing without an intervening `seekg`/`seekp` (the standard requires it; mixing reads and writes without seeking is UB on many implementations).
- **Use binary mode for byte-precise work.** Text mode does `'\n'` ↔ `"\r\n"` translation on Windows, which makes `seekg` byte offsets inconsistent with what you wrote.

## Code in this folder
- `main.cpp` — writes a fixed-record file in binary mode, then:
  1. uses `seekg(0, end) + tellg` to report file size,
  2. seeks to record N and reads it,
  3. opens read+write `fstream`, modifies record N in place.
- File lives in `std::filesystem::temp_directory_path()` and is cleaned up.

## Gotchas
- **Text-mode seeking is fragile.** `tellg()` on a text file returns an opaque value usable only as input to `seekg` — *not* a byte count. Want byte counts? Open in binary.
- **`tellg()` on an unopened or failed stream returns `-1`** (pos_type(-1)). Always check the stream state.
- **`fstream` mode quirk:** opening with `in|out` alone won't *create* the file; add `trunc` to start fresh, or `app` to append.
- After seeking to mid-file and writing in text mode, line endings can shift the file underneath you (Windows). Reach for binary mode whenever you care about exact bytes.

## Run
    make 28.07
