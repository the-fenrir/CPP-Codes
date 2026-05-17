# 13.14 — Class template argument deduction (CTAD) and deduction guides

> learncpp.com: https://www.learncpp.com/cpp-tutorial/class-template-argument-deduction-ctad-and-deduction-guides/

## Why it matters
Spelling out `Pair<int> p{ 1, 2 };` when the compiler can see the arguments is `int`s is busywork. C++17's CTAD lets you write `Pair p{ 1, 2 };` and the compiler figures it out. Same feature `std::vector v{ 1, 2, 3 };` already uses.

## Key points
- **CTAD** (C++17): with no `<>` after the template name, the compiler deduces the template arguments from the constructor arguments. `Pair p{ 1, 2 };` → `Pair<int>`.
- For **aggregate** class templates, C++17 needed an explicit **deduction guide**: `template <typename T> Pair(T, T) -> Pair<T>;`. **C++20** lifts that restriction — aggregate CTAD works without a guide.
- CTAD applies at the **declaration**; you can't CTAD-deduce a return type or a function parameter type.
- All template arguments must be deducible. If only some can be deduced, CTAD fails.
- CTAD is a syntactic convenience. The instantiated type is identical to what you'd get spelling it out.

## Code in this folder
- `main.cpp` — `Pair<T>` with both CTAD usage and an explicit deduction guide (the guide is harmless under C++20 and required under C++17).

## Gotchas
- `Pair p{ 1, 2.0 };` (different types for `T`) is **ambiguous** under CTAD — the compiler can't pick one `T`. Either use a two-parameter template or spell the type out.
- A deduction guide that contradicts the constructor (or aggregate shape) is a hard-to-diagnose error.

## Run
    make 13.14
