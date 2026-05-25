# 19.4 — Pointers to pointers and dynamic multidimensional arrays

> learncpp.com: https://www.learncpp.com/cpp-tutorial/pointers-to-pointers/

## Why it matters
A pointer to a pointer (`T**`) is occasionally necessary — most commonly when you want to dynamically allocate a 2D structure whose row count and/or column count aren't compile-time constants. The mechanics are tedious enough that this lesson is really a warning sign: if you find yourself reaching for `T**`, ask whether a flat `std::vector<T>` with index math, or a `std::vector<std::vector<T>>`, would do.

## Key points
- `int** pp;` declares a pointer to `int*`. `*pp` is an `int*`; `**pp` is the `int`.
- **Array of pointers:** `int** rows = new int*[r];` — useful when each row is allocated separately.
- **Rectangular 2D, columns known at compile time:** `int (*grid)[5] = new int[r][5];` — single allocation, contiguous memory, freed with one `delete[]`.
- **Jagged 2D, both dimensions runtime:** `new int*[r]`, then loop and `new int[cols_i]` for each row. Deallocation order is the reverse: free each row, then the outer array.
- **Flatten trick:** allocate one block of `r * c` ints, index as `data[row * c + col]`. One `new[]`, one `delete[]`, cache-friendly, fewer bugs. This is what `std::vector` + index math does internally.
- `int***` and beyond exist but are almost always a sign that the data structure is wrong.

## Code in this folder
- `main.cpp` — three variants of the same 3×4 grid:
  1. jagged: array of row pointers, each row independently allocated;
  2. flattened: one `new int[rows*cols]`, indexed by hand;
  3. (commented) modern: `std::vector<std::vector<int>>`.

  The flat form is the one to remember.

## Gotchas
- Cleanup order matters: for jagged 2D, `delete[]` each row *before* `delete[]`-ing the outer array. The other way around leaks every row.
- `new int*[r]` only allocates the row-pointer array, not the rows themselves. Forgetting the inner loop leaves you with `r` uninitialized pointers and an immediate crash on first use.
- Double-pointer parameters in C APIs (`int** out`) usually mean "the function will allocate a buffer and store the pointer in `*out`." Read the docs carefully — you almost always own the buffer afterward.
- Modern alternative: a flat `std::vector<int>` sized `rows*cols` is faster, simpler, leak-proof, and easier to pass around.

## Run
    make 19.04
