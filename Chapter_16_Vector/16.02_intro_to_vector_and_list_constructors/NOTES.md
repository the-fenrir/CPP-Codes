# 16.2 — Introduction to std::vector and list constructors

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-stdvector-and-list-constructors/

## Why it matters
`std::vector` is a class template: you spell the element type once, you get a fully working dynamic array. Knowing the *constructors* matters because the syntax overlap between `( )` and `{ }` controls which one fires — and "create a 10-element vector of zeros" vs. "create a vector containing one element with value 10" use the same parens until you switch braces.

## Key points
- `#include <vector>`. Type: `std::vector<T>`.
- **List constructor** uses braces and fills with those values: `std::vector<int> v{ 1, 2, 3 };` — length 3.
- **Length constructor** uses parens and creates that many default-initialized elements: `std::vector<int> v(10);` — length 10, all zero.
- The two are **not interchangeable**. `std::vector<int>{ 10 }` is *one element with value 10*, not 10 elements.
- **CTAD** (class template argument deduction, C++17): `std::vector v{ 1, 2, 3 };` — the `<int>` is deduced from the initializer.
- `std::vector` can be `const`: `const std::vector v{ 1, 2, 3 };` — elements cannot be reassigned.
- `constexpr std::vector` is **not** allowed (heap allocation). Use `std::array` for compile-time fixed-size data.

## Code in this folder
- `main.cpp` — list vs. length constructor, CTAD, and a `const` vector.

## Gotchas
- `std::vector<int> v(3, 5);` — length-and-fill: 3 elements all `5`. Different again from `{ 3, 5 }` (two elements: `3, 5`).
- Default-initialized fundamental types via the length constructor are **value-initialized to 0**. (Don't confuse with uninitialized C-style arrays.)
- Mixed brace/paren styles are a classic interview gotcha; pick brace-init for everything *except* when you genuinely want the length constructor.

## Run
    make 16.02
