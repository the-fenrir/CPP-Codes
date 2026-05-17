# 4.3 — Object sizes and the `sizeof` operator

> learncpp.com: https://www.learncpp.com/cpp-tutorial/object-sizes-and-the-sizeof-operator/

## Why it matters
The C++ standard guarantees **minimum** sizes for fundamental types, not exact sizes. If you assume `int` is 4 bytes everywhere, your code is one cross-compile away from being wrong. `sizeof` lets you ask the compiler directly.

## Key points
- An *n*-bit type stores 2^*n* distinct bit patterns. For signed integers, the range is split roughly half negative, half non-negative.
- Standard guarantees (minimums): `char` = exactly 1 byte; `short` ≥ 2; `int` ≥ 2 (almost always 4 on real systems); `long` ≥ 4; `long long` ≥ 8. `sizeof(char) == 1` is the one promise about exact size.
- `sizeof(T)` and `sizeof expr` return a compile-time `std::size_t` byte count. No parentheses needed for an expression — `sizeof x` works.
- A "byte" in C++ is whatever `CHAR_BIT` says, which is 8 on every platform you'll touch.
- Picking smaller types rarely makes code faster — modern CPUs are tuned for register-width (32/64-bit) operations. Optimize for clarity first.

## Code in this folder
- `main.cpp` — prints `sizeof` for every fundamental type on this machine and a `static_assert` example pinning down an assumption.

## Gotchas
- `sizeof(char) == 1` always, but a "byte" might not be 8 bits on exotic hardware. On x86/ARM/anything you care about, it is.
- `sizeof` on an array gives the **total** size in bytes, not the element count. Element count is `sizeof(arr) / sizeof(arr[0])` — and even that only works on a real array, not a decayed pointer.

## Run
    make 4.03
