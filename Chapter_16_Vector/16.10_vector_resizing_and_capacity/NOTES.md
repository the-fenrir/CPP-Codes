# 16.10 — std::vector resizing and capacity

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdvector-resizing-and-capacity/

## Why it matters
A vector has **two** numbers, not one: its **length** (`size()`, how many elements are alive) and its **capacity** (`capacity()`, how much storage is reserved). Knowing the difference is the difference between writing fast `push_back` code and accidentally O(n²) code.

## Key points
- `size()` — number of constructed elements. `capacity()` — number of slots before a reallocation is needed.
- `capacity >= size` always.
- **`resize(n)`** changes the length to `n`. If growing, default-constructs new elements; if shrinking, destroys excess. *Capacity may grow* but never shrinks.
- **`reserve(n)`** asks for capacity ≥ n. Does **not** change the length; new slots are not yet elements. Use it when you know the final size — avoids repeated reallocations.
- **`shrink_to_fit()`** is a non-binding request to release excess capacity. Implementation may ignore it.
- Reallocation cost: a `push_back` past capacity allocates a new bigger block, **copies/moves every element**, then frees the old block. Capacity typically doubles, giving *amortized* O(1) push_back.
- After reallocation, **all pointers, references, and iterators into the vector are invalidated**.

## Code in this folder
- `main.cpp` — print size and capacity through `push_back`, then show `reserve` flattening the growth curve.

## Gotchas
- `resize(n)` and `reserve(n)` are different verbs. Resize changes *length*. Reserve changes *capacity*.
- Holding a `T*` or `T&` to a vector element across a `push_back` is undefined behavior. (See 16.11 for the canonical bug.)
- Capacity growth strategy is implementation-defined; don't depend on the exact doubling factor.

## Run
    make 16.10
