# 17.1 — Introduction to `std::array`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-stdarray/

## Why it matters
A C-style array (`int a[5]`) has no length stored in its type, decays to a pointer at the slightest provocation, and can't be returned or copied normally. `std::array<T, N>` is the same fixed-size memory layout — zero overhead — but it's a proper value type: knows its own size, copyable, assignable, returnable, works with the algorithms library. Default to `std::array` when the size is known at compile time and `std::vector` when it isn't.

## Key points
- `#include <array>`. Declaration: `std::array<int, 5> a;` — type and size are *both* template parameters.
- Both must be constant expressions. `std::array<int, n>` where `n` is a runtime `int` won't compile.
- List-initialize with braces: `std::array<int, 3> a { 1, 2, 3 };`. With C++17 CTAD: `std::array a { 1, 2, 3 };` deduces `std::array<int, 3>`.
- `constexpr` is allowed and encouraged: `constexpr std::array primes { 2, 3, 5, 7 };` lives entirely at compile time.
- `a[i]` is unchecked (fast, UB on overflow). `a.at(i)` throws `std::out_of_range`. Use `[]` in tight loops where you've already bounded the index.
- Same underlying layout as a C-style array — passing `a.data()` to a C API is fine.

## Code in this folder
- `main.cpp` — declares a `std::array` three ways (typed, CTAD, `constexpr`), accesses elements with `[]` and `.at()`, demonstrates the throw.

## Gotchas
- Forgetting the size template arg: `std::array<int> a;` is *not* a thing. The size is part of the type.
- `std::array<int, 5> a;` (no initializer) leaves elements with **indeterminate** value for `int`. Use `{}` to value-initialize: `std::array<int, 5> a{};` zeros them.
- Two `std::array<int, 5>` and `std::array<int, 6>` are *different types*. Can't assign or compare across.

## Run
    make 17.01
