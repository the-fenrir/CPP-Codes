# 17.3 — Passing and returning `std::array`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/passing-and-returning-stdarray/

## Why it matters
`std::array<int, 5>` and `std::array<int, 6>` are *different types*. A function that takes `const std::array<int, 5>&` only accepts that exact size. The realistic options are: template on the size, take a `std::span` (C++20), or commit to one size. Returning is symmetric — but mandatory copy elision (C++17) makes returning by value free.

## Key points
- **Always pass by `const T&`** (or `T&` if mutating). Pass-by-value copies the whole buffer.
- To accept *any* size, make it a function template: `template<std::size_t N> void f(const std::array<int, N>& a)`.
- To accept any element type too: `template<typename T, std::size_t N> void f(const std::array<T, N>& a)`.
- C++20 `std::span<const int>` (or `std::span<int>` for mutable) is the modern way: one non-template function that accepts `std::array<int, N>` of any `N`, C-style arrays, `std::vector<int>`, etc.
- Return by value. Mandatory copy elision (C++17) eliminates the copy for prvalues; NRVO usually eliminates it for named locals.

## Code in this folder
- `main.cpp` — a fixed-size taker, a templated taker accepting any size, and a function that returns a `std::array` by value.

## Gotchas
- `void f(std::array<int, 5> a)` quietly copies 20 bytes (or 40 on 64-bit `long`). Multiply by call frequency.
- A template-on-`N` function instantiates a fresh body per size. If you call it with `N = 3, 4, 5, 6` you get four copies. Often fine; sometimes a reason to reach for `std::span`.
- You can't return `std::array<int, dynamicN>`. The size is in the return *type* and must be a constant expression.

## Run
    make 17.03
