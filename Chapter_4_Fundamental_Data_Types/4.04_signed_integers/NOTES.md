# 4.4 — Signed integers

> learncpp.com: https://www.learncpp.com/cpp-tutorial/signed-integers/

## Why it matters
`int` is the workhorse of C++ programs. Knowing its range, what happens at overflow, and how integer division rounds keeps a class of subtle bugs out of your code from day one.

## Key points
- Four signed integer types: `short`, `int`, `long`, `long long`. Each has a minimum width (16, 16, 32, 64 bits respectively); on most desktops `int` is 32-bit, `long` is 32-bit on Windows / 64-bit on Linux + macOS, `long long` is 64-bit.
- Range of an *n*-bit signed integer: `-(2^(n-1))` to `2^(n-1) - 1`. So 32-bit `int`: roughly ±2.1 billion.
- Prefer the short form: `long`, not `long int`. Don't write `signed int` — `int` is signed by default.
- **Signed overflow is undefined behavior**. Not "wraps to negative" — UB. The compiler is allowed to assume it never happens and miscompile your code if you trip it.
- Integer division **truncates toward zero**. `8 / 5 == 1`, `-8 / 5 == -1` (since C++11). The fractional part is discarded, not rounded.

## Code in this folder
- `main.cpp` — prints the limits of each signed integer type, demonstrates integer division truncation, and shows (with a clear UB warning) what triggers signed overflow.

## Gotchas
- "It worked on my machine" is no defense for signed overflow — UB can stay quiet for years and then break on a compiler upgrade.
- Mixed-type arithmetic promotes to a common type. `int / double` is a double divide, not integer division. `5 / 2 == 2`, but `5 / 2.0 == 2.5`.

## Run
    make 4.04
