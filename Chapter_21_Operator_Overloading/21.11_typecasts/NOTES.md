# 21.11 — Overloading typecasts (user-defined conversion operators)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/overloading-typecasts/

## Why it matters
A *typecast operator* lets your class convert itself to another type — `static_cast<int>(myCents)` or `static_cast<bool>(myHandle)`. It's the **inverse** of a converting constructor: a converting constructor lets *some other type* become yours; an `operator T()` lets yours become some other type. Powerful, easy to misuse, and almost always wants `explicit`.

## Key points
- Syntax is weird: no return type written, name is `operator T`.
  - `operator int() const { return m_cents; }`
- Mark them `const` if they don't mutate (almost always).
- **Make them `explicit`** by default. Implicit user-defined conversions chain with builtin conversions and silently turn your class into something else in surprising contexts (`if (cents)`, `cents + 5`, function arguments).
- `explicit operator bool()` is the standard "is this object in a valid/non-empty state" idiom — what `std::unique_ptr`, `std::optional`, and stream classes use to make `if (ptr)` work.
- Pre-C++11 didn't allow `explicit` on conversion operators. Lots of older code uses the "safe bool idiom" workaround; just use `explicit operator bool()` now.

## Code in this folder
- `main.cpp` — `Cents` with `explicit operator int()`; a `Handle` with `explicit operator bool()` used in an `if`.

## Gotchas
- Without `explicit`, `operator int()` makes `cents + 5` ambiguous or wrong — the compiler can either call your `operator+` or convert `cents` to `int` and use builtin `+`. Both compile; only one is right.
- A non-`explicit` `operator bool()` lets your object accidentally participate in `int` arithmetic via `bool → int`. `auto n = myHandle + 1;` compiles. Use `explicit`.
- Don't write *both* `operator T()` and a converting constructor `T(YourClass)` — that's a round-trip ambiguity factory.

## Run
    make 21.11
