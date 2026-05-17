# 11.6 — Function templates

> learncpp.com: https://www.learncpp.com/cpp-tutorial/function-templates/

## Why it matters
Overloading lets you write `add(int, int)` and `add(double, double)` separately — but they're the same code. Function templates let you write *one* `add` that works for any type that supports `+`. The compiler stamps out a concrete function per type you actually use. This is the engine behind `std::max`, `std::sort`, and most of the standard library's algorithms.

## Key points
- Syntax: `template <typename T> T add(T x, T y) { return x + y; }`.
  - `typename` and `class` are interchangeable in this position; `typename` reads better for non-class types.
- `T` is a **type template parameter** — a placeholder filled in when the template is *instantiated*.
- A function template is not a function — it's a recipe. No code is generated until you call it.
- The compiler **deduces** `T` from the call's argument types: `add(2, 3)` ⇒ `T = int`. No conversions during deduction (11.7).
- You can force a type explicitly: `add<double>(2, 3)` — `2` and `3` then convert to `double` before the call.
- C++20 **abbreviated function template**: `auto add(auto x, auto y) { return x + y; }` — each `auto` becomes its own independent template parameter (same as `template <typename T, typename U>`).

## Code in this folder
- `main.cpp` — `bigger()` template called for int, double, and `std::string` (named `bigger` not `max` to avoid ADL clashing with `std::max` once `<string>` is included). Also a C++20 abbreviated form.

## Gotchas
- Template *instantiations* are full functions in the binary — using `max` for 7 different types means 7 functions.
- If `T` doesn't support the operation in the body, you get a long error at the *instantiation* site, not at the template definition.
- Compiler can't deduce `T` for: arguments of different types when `T` is shared (`add(1, 2.0)` — `int` vs `double`). Either cast, supply `T` explicitly, or use two parameters (11.8).

## Run
    make 11.06
