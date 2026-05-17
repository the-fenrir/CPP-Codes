# 11.5 — Default arguments

> learncpp.com: https://www.learncpp.com/cpp-tutorial/default-arguments/

## Why it matters
A default argument lets one function declaration cover several call shapes: `print()`, `print(x)`, `print(x, y)`. It removes the need to write trivial overloads, but mixes badly with *real* overloads — most "why won't this compile?" stories with overloading involve a stray default arg.

## Key points
- Syntax: `void f(int x, int y = 0);`. Caller may omit the trailing argument.
- **All defaulted parameters must be rightmost.** Once one parameter has a default, every parameter to its right must also have one.
- Defaults are declared at most once across header/source — usually in the header. The .cpp definition repeats only the parameter, not the `= ...`.
- Defaults **do not differentiate overloads.** `f(int)` and `f(int, int = 0)` look interchangeable at a single-arg call site and produce an *ambiguous match* error.
- Defaults are evaluated at the *call site* — they're not part of the function's stored signature.

## Code in this folder
- `main.cpp` — one function with two defaulted params; calls demonstrate each shape; a commented-out overload section shows the ambiguity trap.

## Gotchas
- Don't redeclare defaults in both header and source — the compiler will see "default arg specified twice".
- A default argument is part of the *declaration the caller sees*. If you add a default to a function only in the .cpp, callers including only the header won't get it.
- Quiz Q1b: `void print()` + `void print(int = 0)` is ambiguous on `print()`.

## Run
    make 11.05
