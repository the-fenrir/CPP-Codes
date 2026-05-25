# Chapter 28 — Summary & recap

> learncpp.com does **not** publish a Chapter 28 summary/quiz page. The "Next lesson" link after 28.7 goes to Appendix A.1. This file is a recap; `quiz_solutions.cpp` is a small end-to-end demo that exercises every feature in the chapter.

## One-page recap

### The model (28.1)
- A **stream** is a buffered sequence of bytes between your program and a sink/source. Same abstraction for terminal, file, and string buffer.
- Hierarchy: `ios_base` → `ios` → `istream`/`ostream` → `iostream`. File/string streams inherit from those: `ifstream : istream`, `stringstream : iostream`, etc.
- Four standard objects: `cin` (istream), `cout` (buffered ostream), `cerr` (unbuffered ostream), `clog` (buffered ostream to stderr).

### Input (28.2)
- `>>` skips leading whitespace, stops at next whitespace, leaves the rest in the buffer.
- `get(buf, N)` keeps the delimiter; `getline(buf, N)` consumes it.
- For `std::string`: non-member `std::getline(in, str)` is the workhorse.
- The classic mixed-mode bug: `>>` followed by `getline` ⇒ empty string. Fix with `>> std::ws` between them.
- Helpers: `peek()`, `unget()`, `putback(ch)`, `ignore(n, delim)`, `gcount()`.

### Output (28.3)
- Two interfaces, one state: `setf`/`unsetf` flags **or** manipulators (`std::hex`, `std::boolalpha`, `std::fixed`, …). Prefer manipulators.
- **Sticky** (persist): base, boolalpha, fixed/scientific, precision, fill, justification.
- **One-shot** (next op only): `std::setw` / `width()`. After one insertion, width resets to 0.
- Precision means *significant digits* by default; *digits after the point* once `std::fixed` or `std::scientific` is active.
- Save/restore flags around helper functions: `auto old = cout.flags(); ... cout.flags(old);`.

### String streams (28.4)
- `<sstream>` gives you `istringstream`, `ostringstream`, `stringstream` — same operators, in-memory buffer.
- `str()` / `str("...")` get/set the underlying string.
- Reuse pattern: `ss.str(""); ss.clear();` — both reset content **and** clear failbit/eofbit.
- The pre-`std::format` way to convert numbers ↔ strings with formatting.

### Stream state & validation (28.5)
- Bits: `goodbit`, `failbit` (recoverable), `eofbit`, `badbit` (don't bother recovering).
- Query: `good()`, `fail()`, `eof()`, `bad()`; stream's `operator bool` is `!fail()`.
- Recovery: `clear()` + `ignore(numeric_limits<streamsize>::max(), '\n')`.
- The trap: `cin >> n` on `"34abcd"` **succeeds** (n=34) and leaves garbage. `fail()` is false. Either peek, or read a line + parse with `std::from_chars`.

### Basic file I/O (28.6)
- `<fstream>`: `ifstream`, `ofstream`, `fstream`. Construct with a path ⇒ open. Destructor ⇒ close (RAII).
- Modes: `in`, `out`, `app`, `ate`, `trunc`, `binary`. Default for `ofstream` truncates — pass `std::ios::app` to append.
- Always check `if (!stream)` immediately after open.
- Line idiom: `while (std::getline(in, line))`.

### Random file I/O (28.7)
- `seekg`/`seekp` to move the position; `tellg`/`tellp` to query it.
- Direction flags: `ios::beg`, `ios::cur`, `ios::end`. Negative offsets work with `end`.
- File-size idiom: seek to end, `tellg`, seek back.
- `fstream` for read+write — needs a `seek` between mode switches.
- Use **binary** mode whenever byte offsets matter (text mode mangles newlines on Windows).

## Code in this folder
- `quiz_solutions.cpp` — a small "round-trip" program that exercises the whole chapter:
  1. builds a formatted record string with `ostringstream`,
  2. validates a numeric field with the modern parse-from-string idiom,
  3. writes records to a temp file (28.6),
  4. seeks to record N in binary mode and reads it back (28.7),
  5. cleans up.

## Run
    make 28.x
