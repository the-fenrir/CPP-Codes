# 8.12 — Halts (exiting your program early)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/halts-exiting-your-program-early/

## Why it matters
The normal way a program ends is `main` returning. Sometimes you can't get there — a config file is missing, an invariant was violated, the user asked to quit deep in the call stack. The standard library gives you several ways to stop the program right now, and they're **not** equivalent: some run destructors and global cleanup, some don't. Picking the wrong one can leak files, skip database commits, or print garbage from a half-flushed buffer.

## Key points
- **Returning from `main`** — the normal exit. Runs destructors of all local objects, then calls each registered atexit handler, then destructors of static storage objects, then flushes streams. This is the only "clean" exit.
- **`std::exit(code)`** (from `<cstdlib>`) — terminate the program. Static-storage destructors run; atexit handlers run; streams flushed. **Local destructors of currently-active functions do NOT run** (the stack is not unwound). Don't call from inside a function that owns scope-bound resources.
- **`std::abort()`** — slam the door. No destructors, no flushing. Used internally by `assert()` on failure. Generates a core dump on Unix. Almost never appropriate as an intentional exit.
- **`std::quick_exit(code)`** — like `exit` but runs only `at_quick_exit` handlers, not destructors. Rarely needed.
- **`std::terminate()`** — what runs when an exception escapes everything. By default calls `abort()`. Not normally something you call yourself.
- Exit codes: `0` = success, non-zero = failure. Constants in `<cstdlib>`: `EXIT_SUCCESS`, `EXIT_FAILURE`. Anything else is convention.

## Code in this folder
- `main.cpp` — registers an `atexit` handler, builds a tiny RAII guard whose destructor prints, and demonstrates the **difference** between returning from `main` and calling `std::exit`. Two side-by-side runs would diverge; here we do one clean `return` so the build always succeeds, but the commented `std::exit` line shows what would change.

## Gotchas
- `std::exit` skipping local destructors means: open files don't flush, mutexes don't release, scope guards don't run. If your code relies on RAII for correctness (and modern C++ usually does), prefer `return` from main and let normal unwinding happen.
- `assert()` in release builds (compiled with `NDEBUG`) is a no-op. Don't put side effects (`assert(file.open(...))`) inside it.
- `abort()` from a signal handler is fine; `exit()` is **not** signal-safe — calling it from a signal handler is undefined behavior.

## Run
    make 8.12
