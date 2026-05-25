# 28.4 — Stream classes for strings

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stream-classes-for-strings/

## Why it matters
You already know `<<` and `>>` for I/O. `<sstream>` lets you point those same operators at a *string buffer in memory* — which means parsing, formatting, and number↔string conversion all collapse into the stream API you already use. It's the standard way to: split a string into tokens, build a formatted message before printing, or convert `int`/`double`/etc. to `std::string` without pulling in `<format>` (pre-C++20) or `printf`.

## Key points
- Three classes (header `<sstream>`):
  - `std::istringstream` (extract-only, derives from `istream`)
  - `std::ostringstream` (insert-only, derives from `ostream`)
  - `std::stringstream`  (both, derives from `iostream`)
- **Get/set the buffer with `str()`:**
  - `ss.str()` returns the buffered string.
  - `ss.str("...")` replaces it.
- **Two ways to load data in:** `ss << value` (formatted) or `ss.str("text")` (raw).
- **Two ways to read out:** `ss >> value` (tokenized) or `ss.str()` (whole buffer).
- **Reuse pattern:** to reuse a stream, both reset the buffer *and* clear error flags:
  ```cpp
  ss.str("");
  ss.clear();   // reset eof/fail bits — without this, reuse silently fails
  ```
- **Number ↔ string:** the canonical pre-`std::format` recipe. For new code, `std::to_string` / `std::stoi` / `std::from_chars` are often simpler — but `stringstream` is what you reach for when format flags matter.

## Code in this folder
- `main.cpp` — round-trips numbers through a `stringstream`, tokenizes a CSV-ish line with `istringstream`, builds a formatted message with `ostringstream`, and shows the `str("") + clear()` reuse idiom.

## Gotchas
- After extracting past the end, the stream's `failbit` is set. Subsequent inserts will *succeed* but extracts won't — until you `clear()`.
- `ss.str()` returns a *copy*. Don't take a `const char*` from it expecting it to live forever:
  `const char* p = ss.str().c_str();  // dangling — the temporary string died`.
- `ostringstream` doesn't shrink. If you reuse it for many small messages, `str("")` keeps the capacity but resets the content — usually fine.

## Run
    make 28.04
