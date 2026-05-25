# 17.7 — Introduction to C-style arrays

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-c-style-arrays/

## Why it matters
C-style arrays are baked into the language — string literals are them, multidimensional arrays in low-level code use them, and every legacy C interface speaks them. You should never *reach* for one in new code (use `std::array` or `std::vector`), but you'll read them constantly, so know the rules: how to declare, initialize, size-deduce, and identify the dangerous corners.

## Key points
- Declaration: `int arr[5];` — uninitialized `int`s, indeterminate values.
- The size must be a constant expression in standard C++ (VLAs are a GCC extension, not portable; turn `-pedantic` on and they warn).
- Aggregate initialization: `int arr[5] { 1, 2, 3 };` — first 3 set, last 2 value-initialized to 0.
- Empty braces: `int arr[5] {};` — all zero. **Always do this** if you don't have explicit values.
- Omitted size: `int arr[] { 1, 2, 3 };` — size deduced to 3. Often combined with `std::size(arr)`.
- `std::size(arr)` (in `<iterator>`) returns the element count *as long as you haven't decayed it to a pointer*. `sizeof(arr) / sizeof(arr[0])` is the C-era version of the same idea.
- Element access: `arr[i]`, unchecked, UB on overflow. No `.at()`.

## Code in this folder
- `main.cpp` — three flavors of declaration (sized, partially initialized, deduced size), `std::size()` to recover the length, and a loop.

## Gotchas
- `int arr[5];` doesn't zero-initialize. `int arr[5] {};` does. Different.
- Two C-style arrays don't compare with `==`. `arr1 == arr2` compiles but compares *pointers*, not contents. (Compilers warn, but the bug is real.)
- Can't return a C-style array from a function. Can't assign one to another. Can't pass by value (it decays — see 17.8). This is why `std::array` exists.

## Run
    make 17.07
