# 16.4 — Passing std::vector

> learncpp.com: https://www.learncpp.com/cpp-tutorial/passing-stdvector/

## Why it matters
Passing a `std::vector` by value copies *every element* — a 10-million-int vector copies 10 million ints. By reference is almost always what you want; by const reference if you don't intend to mutate. The hard part is keeping the function flexible across different element types.

## Key points
- **Default**: pass by `const std::vector<T>&`. No copy; can't accidentally mutate.
- **Mutating**: pass by `std::vector<T>&` (no `const`). Caller's vector changes.
- **Pass by value** only when you need an independent local copy (then you might as well take by value and move-from).
- Different element types ⇒ the function must be a **template** (function templates from Ch. 11): `template <typename T> void f(const std::vector<T>& v)`.
- Or take `const auto&` parameter (C++20 abbreviated template): `void f(const auto& v)`.
- Avoid C-style pointers + length pairs. Pass the vector itself; it knows its size.

## Code in this folder
- `main.cpp` — by-value vs. by-reference (cost), const-ref read-only, and a template that works for any element type.

## Gotchas
- `std::vector<int>` and `std::vector<double>` are *different types*. A function parameter of one will refuse the other — you need a template (or two overloads).
- Templates must live in headers (or in the same translation unit as the call). See 11.x and 15.05.

## Run
    make 16.04
