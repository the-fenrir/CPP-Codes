# 21.9 — Overloading `operator[]`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/overloading-the-subscript-operator/

## Why it matters
`a[i]` is the idiom for "the i-th element of `a`." Container-like types (vectors, arrays, hash maps, custom matrices) overload `operator[]` to give callers that syntax. `operator[]` **must** be a member function — its left operand is always your object.

## Key points
- Two overloads, by const-ness of the receiver:
  - `T& operator[](std::size_t i);` — usable on the left of `=`.
  - `const T& operator[](std::size_t i) const;` — usable on a `const` instance.
- Returning by reference is what allows `arr[3] = 42;`. Returning by value silently turns mutation into a no-op on a temporary.
- Indices should usually be `std::size_t` (unsigned). Bounds-check with `assert` for "this is a programmer bug" or throw `std::out_of_range` for "this is a runtime error the caller can recover from."
- C++23 lets you write multi-arg `operator[]` (`m[i, j]`). Pre-23 the comma operator quietly took only the last value, which is why people used `operator()` for matrix indexing (next lesson).

## Code in this folder
- `main.cpp` — an `IntList` (fixed size) with both `[]` overloads.

## Gotchas
- The two overloads differ **only** in the trailing `const` and the return type's const-ness. Forgetting either makes one of the call sites fail to compile.
- Don't return a copy by accident. `int operator[](size_t)` compiles fine but breaks `arr[i] = 5;` silently — the assignment goes into a discarded temporary.
- An empty assert is not a bounds check; either `assert(i < n)` or throw.

## Run
    make 21.09
