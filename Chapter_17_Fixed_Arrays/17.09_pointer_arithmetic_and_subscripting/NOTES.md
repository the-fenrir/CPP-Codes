# 17.9 — Pointer arithmetic and subscripting

> learncpp.com: https://www.learncpp.com/cpp-tutorial/pointer-arithmetic-and-subscripting/

## Why it matters
Once you understand decay (17.8), the indexing operator `arr[i]` on a C-style array is *defined as* `*(arr + i)` — pointer arithmetic in syntactic disguise. The "type-aware step" (advancing by `sizeof(T)` bytes, not 1) is what makes `p + 1` mean "next element" instead of "next byte." This is the basis of iterator design and the reason `p[i]` and `i[p]` are equivalent (yes, really).

## Key points
- For a `T*` `p`: `p + n` is `p` advanced by `n * sizeof(T)` bytes — i.e. `n` elements forward.
- `p - q` (two `T*`s into the same array) returns a `std::ptrdiff_t` element count.
- `p[i]` is *defined* as `*(p + i)`. So is `i[p]` — commutative because `+` is. (Don't write `i[p]`; it's a parlor trick.)
- An iterator-style loop walks pointers: `for (int* p = arr; p != arr + N; ++p)`. Equivalent to indexing in performance and intent; modern code uses range-`for`.
- "One past the end" pointer is *legal to form* (`arr + N`) but illegal to dereference. It's how loops terminate.
- Arithmetic on pointers to *different* arrays, or outside `[arr, arr+N]`, is undefined behavior — not just unspecified, full UB.

## Code in this folder
- `main.cpp` — show `arr[i] == *(arr + i)`, walk an array with pointer arithmetic, compute differences with `std::ptrdiff_t`.

## Gotchas
- `p + 1` advances by `sizeof(T)` bytes. Cast through `char*` (or `std::byte*`) for byte arithmetic.
- Adding/subtracting `int` vs. `size_t` can warn on signedness. Use `std::ptrdiff_t` for differences.
- `&arr[N]` (i.e. dereferencing one-past) is UB even if you immediately take its address. Use `arr + N`.

## Run
    make 17.09
