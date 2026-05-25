# 28.5 — Stream states and input validation

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stream-states-and-input-validation/

## Why it matters
`std::cin >> n` where the user types "abc" doesn't throw, doesn't return an error code — it silently sets `failbit` and leaves `n` unchanged. Every subsequent read also fails until you clear the state *and* drain the bad input. This is where most beginner programs hang or loop forever, and where most real-world C++ programs do input validation manually.

## Key points
- **State bits** (in `std::ios_base`):
  - `goodbit`  — no flags set, healthy stream.
  - `failbit`  — last operation failed (wrong type, hit EOF mid-read). Recoverable.
  - `eofbit`   — reached end of input.
  - `badbit`   — stream is fundamentally broken (rare; e.g. underlying device error). Treat as unrecoverable.
- **Query**: `good()`, `fail()`, `bad()`, `eof()`, `rdstate()`. `operator!` and `operator bool` on the stream are shorthand for `fail()` / `!fail()`.
- **Recovery recipe** (after a failed numeric read):
  ```cpp
  std::cin.clear();    // reset all error bits
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // drain
  ```
- **The "34abcd" trap.** `cin >> n` reads `34` successfully and leaves `"abcd\n"` in the buffer. The stream is "good" but the input was garbage. Check by peeking, or — preferred — extract a `std::string` first and parse with `std::from_chars` / `stringstream`.
- **Modern approach:** read the whole line as `std::string`, validate, then parse. Eliminates the entire stream-state dance.

## Code in this folder
- `main.cpp` — three input scenarios driven by `istringstream` (so it runs under `make`):
  1. clean integer input,
  2. completely bad input (`"abc"`) and the clear/ignore recovery,
  3. mixed `"34abcd"` extracting 34 + garbage, detected via `peek` and via the parse-from-string idiom.

## Gotchas
- `clear()` with no arg resets *all* bits to `goodbit`. `clear(std::ios::badbit)` *sets* badbit — almost never what you want.
- `eof()` is true only *after* an attempted read past the end. Don't use it as a loop condition; use the stream's bool conversion (`while (std::getline(in, line))`).
- `cin.fail()` after a successful but partial read (the `34abcd` case) is **false** — fail() alone is not sufficient validation.

## Run
    make 28.05
