# 11.9 — Non-type template parameters

> learncpp.com: https://www.learncpp.com/cpp-tutorial/non-type-template-parameters/

## Why it matters
Type template parameters parametrize *types* (`vector<int>` vs. `vector<double>`). **Non-type template parameters (NTTPs)** parametrize *values* — `std::array<int, 16>` vs. `std::array<int, 32>`. The size is part of the type, known at compile time, and the compiler can use it for optimization, bounds checks, etc. NTTPs are how `std::array` can be stack-allocated and how `std::bitset<N>` knows its width.

## Key points
- Syntax: `template <int N> void f();` or `template <std::size_t N> ...`.
- The NTTP must be a **constant expression** at the call site: `f<8>()` works; `int x = 8; f<x>()` doesn't unless `x` is `constexpr`.
- Allowed NTTP types: integral, enums, pointers/references to objects with static storage, `nullptr_t`, and (since C++20) `auto` plus structural types.
- C++20 lets you write `template <auto N>` — type is deduced from the argument.
- Inside the template, `N` is a regular compile-time constant; you can use it in array sizes, `static_assert`, template-recursion termination, etc.

## Code in this folder
- `main.cpp` — `Factorial<N>` computed at compile time; a `print_n_times` function that unrolls via NTTP; a `static_assert` showing it's all compile-time.

## Gotchas
- Each value produces a separate instantiation — `f<1>`, `f<2>`, … are different functions and bloat the binary if N varies widely.
- Floats/doubles weren't allowed as NTTPs until C++20 (still rare in practice).
- Passing `std::size_t` where `int` is the NTTP type can cause deduction surprises — match the declared NTTP type.

## Run
    make 11.09
