# 28.1 — Input and output (I/O) streams

> learncpp.com: https://www.learncpp.com/cpp-tutorial/input-and-output-io-streams/

## Why it matters
Every "print to screen" and "read from keyboard" you've written so far has been a stream operation, but you've been treating `std::cin` and `std::cout` as magic globals. This lesson finally explains the model: a stream is a buffered sequence of bytes flowing between your program and *something* (terminal, file, string, network). Once you know it's the same abstraction for all of them, file I/O and `stringstream` stop feeling like new APIs — they're the same `<<` / `>>` you already know, pointed at a different sink.

## Key points
- **Stream** = a sequence of bytes accessed sequentially, with an internal buffer that decouples your code from the device's speed.
- **Input stream** (source → program): data flows in; you pull with `>>` (extraction).
- **Output stream** (program → sink): data flows out; you push with `<<` (insertion).
- Standard objects (all defined in `<iostream>`):
  - `std::cin`   — input from stdin (an `istream`).
  - `std::cout`  — output to stdout (an `ostream`), line-buffered when attached to a terminal.
  - `std::cerr`  — error output, **unbuffered** — errors hit the terminal immediately even if the program crashes.
  - `std::clog`  — error output, **buffered** — same destination as `cerr` typically, but cheaper for high-volume logging.
- Class hierarchy (simplified):
  - `ios_base` → `ios` → `istream`, `ostream`
  - `iostream` inherits from both (diamond, resolved by virtual inheritance — hence the warning to be careful with multiple inheritance).
  - File and string streams derive from these: `ifstream : istream`, `ofstream : ostream`, `stringstream : iostream`, etc.

## Code in this folder
- `main.cpp` — demonstrates the four standard streams and proves `cerr` is unbuffered while `cout` is buffered.

## Gotchas
- `std::endl` flushes the buffer; `'\n'` does not. In tight loops this matters — prefer `'\n'`.
- `cerr` being unbuffered is a feature for errors, not free performance — every write is a syscall. Use `clog` for non-critical logging.
- A stream "object" is *not* the device. Closing `cout` doesn't close the terminal; the stream just stops forwarding.

## Run
    make 28.01
