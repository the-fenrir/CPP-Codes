# 16.3 — std::vector and the unsigned length and subscript problem

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdvector-and-the-unsigned-length-and-subscript-problem/

## Why it matters
`v.size()` returns `std::size_t` — an **unsigned** type. The natural loop counter is a signed `int`. Mixing them gives you compiler warnings, weird comparisons, and the world's most frustrating bug: a backwards-iterating loop that wraps around to a huge positive value and runs forever.

## Key points
- `v.size()` → `std::size_t` (alias for an unsigned integer, ≥32 bits, typically 64).
- `operator[]` takes `size_t`. Indexing with `int` triggers a (silent) signed→unsigned conversion.
- `-Wsign-compare` / `-Wconversion` warn when you mix.
- Three common workarounds:
  - **Cast at the boundary**: `static_cast<int>(v.size())`. Works; ugly.
  - **Use `size_t` everywhere**: `for (std::size_t i = 0; i < v.size(); ++i)`. Clean *until* you want to decrement past zero, then you wrap.
  - **`std::ssize` (C++20)**: returns a *signed* size. Cleanest in C++20.
- **`.at(i)`** is the bounds-checked version of `[i]` — throws `std::out_of_range` on miss. Slower; useful while debugging.
- The unsigned-loop trap: `for (size_t i = v.size() - 1; i >= 0; --i)` never terminates. `i >= 0` is always true for unsigned.

## Code in this folder
- `main.cpp` — three loop styles + the underflow trap, plus `.at()`.

## Gotchas
- `auto i = v.size() - 1;` when `v` is empty: `0u - 1u` = huge positive. Always guard `if (!v.empty())`.
- `.at()` is **not** zero-cost; don't reach for it in tight loops.
- `std::ssize` returns `std::ptrdiff_t`-ish (signed). Pair it with `static_cast<int>` only if you really need `int`.

## Run
    make 16.03
