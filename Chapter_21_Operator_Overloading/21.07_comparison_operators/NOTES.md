# 21.7 — Overloading the comparison operators

> learncpp.com: https://www.learncpp.com/cpp-tutorial/overloading-the-comparison-operators/

## Why it matters
You need `==`, `!=`, `<`, `<=`, `>`, `>=` for sorting, lookup in `std::set`/`std::map`, equality assertions, and so on. Pre-C++20 you wrote all six by hand. **C++20's `operator<=>`** (the spaceship) lets you write *one* function and the compiler synthesises the rest — including `==`/`!=` if you `= default` them.

## Key points
- Pre-C++20 idiom: implement `==` and `<`, then derive `!=`, `>`, `<=`, `>=` in terms of them.
- C++20 idiom:
  - `auto operator<=>(const T&) const = default;` → memberwise spaceship + all six comparisons.
  - `bool operator==(const T&) const = default;` → memberwise equality + free `!=`.
- Return type of `<=>`:
  - `std::strong_ordering` — total order, equal values are substitutable.
  - `std::weak_ordering` — total order, equal-but-not-substitutable (e.g. case-insensitive strings).
  - `std::partial_ordering` — incomparable values exist (e.g. NaN floats).
- Comparison operators should usually be **non-member** (free or friend). With C++20 defaulted spaceship, you instead declare it *inside* the class with `= default`, but it still participates symmetrically.

## Code in this folder
- `main.cpp` — `Car` with a defaulted `<=>` and `==`. Demonstrates that all six comparisons work and that `std::sort` picks them up.

## Gotchas
- `= default`-ing `<=>` compares members **in declaration order**, lexicographically. Reorder members deliberately if a different priority is wanted.
- Floating-point members force `partial_ordering` because of NaN. Don't pretend a `<=>` over `double` is `strong`.
- Pre-C++20 hand-written comparisons must be **consistent** (a < b && b < c ⇒ a < c). Inconsistent comparisons silently corrupt `std::set`/`std::map`.

## Run
    make 21.07
