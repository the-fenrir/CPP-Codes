# 20.5 — Ellipsis (and why to avoid them)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/ellipsis-and-why-to-avoid-them/

## Why it matters
C's `printf` family takes a variable number of arguments via `...` ("ellipsis"). C++ inherits the mechanism. It works, but it throws away the things C++ otherwise gives you — type safety, parameter count checking, automatic promotions — so it's mostly a cautionary tale about *why* modern C++ has variadic templates and `std::format`.

## Key points
- Signature: `int findAverage(int count, ...);` — at least one named param, then `...`.
- Access via the `<cstdarg>` macros: `va_list`, `va_start(list, last_named)`, `va_arg(list, T)`, `va_end(list)`.
- You must tell the function how many arguments there are and what type they are — the language won't. Caller and callee have to silently agree on both.
- Default argument promotions apply: `float` → `double`, `char/short` → `int`, etc. Read with the *promoted* type or you get garbage.
- Type mismatches are undefined behavior, not compile errors. The compiler can't help you.
- **Use instead**:
  - `std::initializer_list<T>` — homogeneous run-time list, known size.
  - Variadic templates (`template<class... Args>`) — heterogeneous, type-safe, compile-time count.
  - `std::format` / `std::print` (C++20/23) — type-safe formatted output.

## Code in this folder
- `main.cpp` — a tiny `findAverage(count, ...)` using `<cstdarg>`, plus the safer equivalents (`initializer_list`, variadic template) for comparison.

## Gotchas
- Pass a `float` to a `va_arg(..., float)` and you'll read garbage — `float` was promoted to `double`. Use `va_arg(..., double)`.
- Pass *fewer* arguments than `count` claims and `va_arg` walks off the end. No diagnostic.
- `va_end` is mandatory — skipping it is UB on some ABIs.

## Run
    make 20.05
