# 11.8 — Function templates with multiple template type parameters

> learncpp.com: https://www.learncpp.com/cpp-tutorial/function-templates-with-multiple-template-types/

## Why it matters
`template <typename T> T add(T, T)` can't handle `add(1, 2.5)` — `T` would have to be `int` and `double` at once, and deduction won't convert. Two type parameters fix it: `T` and `U` are deduced independently. The follow-up question — "what's the *return* type?" — is what `auto` return type and `decltype(auto)` are for.

## Key points
- `template <typename T, typename U> auto add(T x, U y) { return x + y; }` — `T` and `U` are independent.
- **`auto` return type** lets the compiler deduce the result from the `return` expression — necessary when the result type depends on `T+U`.
- Old-style trailing return: `auto add(T x, U y) -> decltype(x + y)` — works pre-C++14, still readable.
- **Abbreviated function template** (C++20): `auto add(auto x, auto y)` is the same as the two-parameter template above.
- Common pitfall: with `T mult(T x, int y)`, `T` is deduced *only* from `x`. `mult(1.5, 3)` ⇒ `T = double`. The second parameter is plain `int`.

## Code in this folder
- `main.cpp` — `add<T,U>`, `mult<T>` with a fixed `int` second param, `sub<T,U>` with `auto` return.

## Gotchas
- `auto` return type triggers another full template-style deduction on the return expression — different rules from explicit return types (no reference / no top-level const). Use `decltype(auto)` if you need to preserve references.
- When return types differ across the function's `return` statements, deduction fails — all returns must agree.
- Two type parameters is not a license to overload by template; if calls are ambiguous (both `T` and `U` could be either type), you'll get a deduction failure.

## Run
    make 11.08
