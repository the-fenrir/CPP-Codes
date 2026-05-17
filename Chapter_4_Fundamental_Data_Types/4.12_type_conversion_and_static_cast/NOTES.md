# 4.12 — Introduction to type conversion and `static_cast`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-type-conversion-and-static_cast/

## Why it matters
C++ converts between types implicitly *all the time* — `int` to `double`, `char` to `int`, signed to unsigned. Most of those conversions are safe; some lose data silently; brace-initialization is the safety net that refuses the lossy ones. `static_cast` is how you say "yes, I really do want this conversion, I accept the consequences."

## Key points
- **Implicit conversion** happens at function calls, assignments, and mixed-type expressions. Passing an `int` where a `double` is expected produces `5.0` from `5` for free.
- **Narrowing conversions** lose information — `double → int` drops the fractional part, `int → short` may overflow. Compilers warn under `-Wconversion`/`-Wnarrowing`.
- **Brace-initialization refuses narrowing conversions**: `int x{ 5.5 };` is a compile error. `int x = 5.5;` compiles with a warning. This is the structural reason chapter 1 told you to brace-init.
- **`static_cast<T>(expr)`** is the explicit, type-checked conversion: tells the compiler "convert `expr` to `T`, I accept any data loss." Suppresses the warning *because you took responsibility*.
- The classic use: print a `char` (or `std::int8_t`) as its numeric value via `static_cast<int>(ch)`.

## Code in this folder
- `main.cpp` — implicit int↔double conversion, the brace-init narrowing rejection (commented), and `static_cast` for both numeric printing and explicit truncation.

## Gotchas
- `static_cast<unsigned int>(-1)` is well-defined (it wraps to UINT_MAX). `static_cast<int>(1e20)` if the value doesn't fit in `int` is undefined behavior in C++17 and earlier, implementation-defined in C++20+. Don't cast values you haven't range-checked.
- Don't reach for the C-style cast `(int)x` — it can silently invoke up to four different conversions including the dangerous `reinterpret_cast` and `const_cast`. `static_cast` is the one to learn first; `reinterpret_cast` / `dynamic_cast` / `const_cast` come later.

## Run
    make 4.12
