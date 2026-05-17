# 3.5 — More debugging tactics

> learncpp.com: https://www.learncpp.com/cpp-tutorial/more-debugging-tactics/

## Why it matters
Ad-hoc prints (3.4) work for a one-off bug but get noisy fast — and you eventually `git commit` something with `std::cout << "HERE"` still in it. This lesson upgrades the technique with three tools: **`std::cerr`** for diagnostic output, **conditional compilation** to toggle debug prints from one switch, and **a logger** for programs whose useful lifetime is longer than one terminal session.

## Key points
- **`std::cerr` over `std::cout`** for debug output: unbuffered (survives crashes), separable from real output via `2>` redirection on the shell, and signals intent to the reader.
- **Conditional compilation** with `#ifdef ENABLE_DEBUG ... #endif` (or a wrapper macro) lets you leave instrumentation in the source and toggle it at build time:
  ```cpp
  #ifdef ENABLE_DEBUG
  #define DBG(x) std::cerr << x << '\n'
  #else
  #define DBG(x)
  #endif
  ```
  Compile with `-DENABLE_DEBUG` to turn it on; without it, the calls cost zero at runtime.
- **A small logger** (3rd-party libs: plog, spdlog) writes to a file with timestamps + severity levels. Worth it once your program runs longer than a terminal or you need a record of yesterday's crash.
- **Don't ship debug instrumentation as live code.** Either guard it with `#ifdef` or remove it before commit. `git grep DBG` before you push.

## Code in this folder
- `main.cpp` — same `countEven` from 3.4, rewritten with a `DBG(x)` macro. Build twice: once normally (silent), once with `-DENABLE_DEBUG` (verbose). The Makefile dispatcher uses `CXXFLAGS`, so:
  ```
  CXXFLAGS="-std=c++20 -Wall -Wextra -Wpedantic -O0 -g -DENABLE_DEBUG" make 3.05
  ```

## Gotchas
- Macros are textually substituted — `DBG(x); else foo();` becomes `; else foo();` and breaks. Always brace the surrounding control flow.
- `std::endl` flushes; `'\n'` doesn't. For crash-survival prints, prefer `std::endl` *or* explicit `<< std::flush`. Otherwise prefer `'\n'` (cheaper).
- A file-based logger that doesn't flush per line will lose the last few entries on crash — exactly when you need them. Configure it to flush on `ERROR` and above.

## Run
    make 3.05
