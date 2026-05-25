# 17.2 — `std::array` length and indexing

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdarray-length-and-indexing/

## Why it matters
`std::array` knows its length, but the language and the library don't agree on how to *say* it. `.size()`, `std::size()`, and the template parameter all give you the same number with different trade-offs (`std::size_t` vs. signed, runtime vs. compile-time). Picking the right one stops sign-conversion warnings and lets you index with a `constexpr` value where it matters.

## Key points
- `a.size()` and `std::size(a)` both return a `std::size_t` (unsigned). For `std::array`, both are `constexpr`.
- C++20: `std::ssize(a)` returns a *signed* type. Useful when subtracting or comparing against a signed loop counter — eliminates `-Wsign-compare` warnings.
- The size is also `std::tuple_size_v<decltype(a)>` (compile time, no instance needed) and `decltype(a)::size()`.
- Indexing operators:
  - `a[i]` — fast, **unchecked**, undefined behavior on overflow. Use when `i` is provably in range.
  - `a.at(i)` — throws `std::out_of_range`. Use when `i` comes from outside.
  - `std::get<I>(a)` — `I` is a template arg, **compile-time bounds check**. Best for known indices in `constexpr` contexts.
- Index type is `std::size_t`. Mixing `int` counter with `size()` triggers signed/unsigned warnings — use `std::size_t count` in your for-loop or convert explicitly.

## Code in this folder
- `main.cpp` — shows `size()` / `std::size()` / `std::ssize()`, the three indexing forms, and a `static_assert` using `std::get<>`.

## Gotchas
- `std::array<int, 0>` is legal. `.empty()` returns `true`. Indexing it is UB.
- `for (int i = 0; i < a.size(); ++i)` warns: `int` vs. `std::size_t`. Either use `std::size_t i` or `std::ssize(a)`.
- `std::get<3>(a)` where `a.size() == 3` is a *compile error*, not a runtime exception — that's the feature, not a bug.

## Run
    make 17.02
