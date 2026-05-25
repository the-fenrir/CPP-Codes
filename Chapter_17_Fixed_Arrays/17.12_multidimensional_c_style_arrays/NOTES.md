# 17.12 — Multidimensional C-style arrays

> learncpp.com: https://www.learncpp.com/cpp-tutorial/multidimensional-c-style-arrays/

## Why it matters
Row-major storage is the foundation: `int g[3][4]` is `3 * 4 = 12` ints laid out as three contiguous rows. The C-style multidimensional form supports nicer initializer syntax and partial type omission (`int g[][4]` — first dimension deduced) that the `std::array<std::array<...>>` form does not. For numerical/graphics code stuck in C-style territory, knowing the layout rules is non-negotiable.

## Key points
- `int g[3][4];` — 3 rows of 4 ints, row-major (`g[r][c]` is element `r*4 + c`).
- Initialize with nested braces: `int g[2][3] { {1,2,3}, {4,5,6} };`. The inner braces are optional under the same elision rules: `int g[2][3] { 1,2,3, 4,5,6 };` works (one big initializer).
- Omit only the **outer** dimension: `int g[][3] { {1,2,3}, {4,5,6} };` deduces to `[2][3]`. Inner dimensions are part of element type and must be present.
- `g[r]` (a row) decays to `int*` *as a row*, not to the whole array. `g` itself decays to `int (*)[4]` — pointer to "array of 4 ints."
- Two-loop traversal: outer over rows, inner over columns. Range-`for` works: `for (auto& row : g) for (int x : row) ...`.

## Code in this folder
- `main.cpp` — declares a 2D grid two ways (full + outer-deduced), prints it row-by-row, sums all elements with nested range-for.

## Gotchas
- `int g[][]` is illegal. Only the leftmost size can be deduced.
- A "ragged" 2D — rows of different lengths — isn't a 2D array. You need `std::vector<std::vector<T>>` (heap pointers per row) or an array of `std::string_view`s.
- `g[r][c]` and `*(*(g + r) + c)` are equivalent. The latter is the actual semantics; the former is sugar.

## Run
    make 17.12
