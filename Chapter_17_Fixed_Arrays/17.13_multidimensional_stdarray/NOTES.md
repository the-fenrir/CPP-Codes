# 17.13 — Multidimensional `std::array`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/multidimensional-stdarray/

## Why it matters
There's no `std::array<int, 3, 4>`. The standard library spells a 2D array as `std::array<std::array<int, 4>, 3>` — an array of rows, each row itself an array. It's the right thing semantically (each row is a real value-type, it can be passed by reference, no decay) but the syntax is heavier and the initializer demands attention to braces (17.4 redux). C++23 introduced `std::mdspan` to make this nicer; pre-23, you live with the nested form.

## Key points
- Type: `std::array<std::array<T, Cols>, Rows>`. Outer = rows, inner = columns. Element access: `g[r][c]`.
- Initialization: outer braces for the outer `std::array`, then nested braces per row. With brace elision the most common form is:
  ```cpp
  std::array<std::array<int, 3>, 2> g {{
      { 1, 2, 3 },
      { 4, 5, 6 }
  }};
  ```
  Note the **double** outer braces — required because `std::array` itself is an aggregate around a C-style array.
- A `using` alias usually saves your sanity: `using Grid = std::array<std::array<int, Cols>, Rows>;`.
- Pass by `const Grid&`. No decay, length safely encoded in the type — fixes most of what's broken about C-style nested arrays.
- Each "row" is a value, not a pointer — you can return it, copy it, compare it (`==` works element-wise on `std::array`).

## Code in this folder
- `main.cpp` — defines a `Grid` alias, initializes a 3x4 grid, sums it with nested range-for, demonstrates row-as-value (copy, compare).

## Gotchas
- The double outer braces aren't optional in the strict form. With brace elision, a single outer set works on most compilers — but if you mix elision levels you'll get a confusing diagnostic.
- C++23 `std::mdspan` is a non-owning view over a flat buffer; it's not a drop-in replacement for nested `std::array`. Different tool, similar use case.
- Memory layout is *still* row-major contiguous — each inner `std::array` sits directly after the previous one. You can `reinterpret_cast` to a flat `int*` if a C API needs it.

## Run
    make 17.13
