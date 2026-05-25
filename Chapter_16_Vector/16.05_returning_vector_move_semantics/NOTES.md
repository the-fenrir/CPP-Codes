# 16.5 — Returning std::vector, and an introduction to move semantics

> learncpp.com: https://www.learncpp.com/cpp-tutorial/returning-stdvector-and-an-introduction-to-move-semantics/

## Why it matters
Returning a `std::vector` looks like it should be expensive — but it isn't, thanks to two compiler features that together make `return v;` the right answer most of the time: **copy elision** (you saw it in 14.15) and **move semantics** (new here). Understanding move is the conceptual seed for everything in Chapter 22.

## Key points
- **Return by value**: `std::vector<int> f() { std::vector<int> v{ ... }; return v; }`. Idiomatic; cheap.
- **Copy elision / NRVO**: the compiler can construct `v` directly in the caller's storage — *zero* copies, *zero* moves.
- When elision doesn't apply, **move construction** kicks in: the vector's three pointers (data, size, capacity) are *stolen* into the new object; the moved-from vector is left empty. O(1), not O(n).
- A **move** is "transfer ownership of the guts." A **copy** is "duplicate the guts." Both work for `std::vector`; move is cheap, copy is not.
- Don't return `const std::vector<T>` — it disables move and forces a copy.
- Don't return a reference or pointer to a local; the local dies at function exit (dangling).

## Code in this folder
- `main.cpp` — return by value (the right way), with the addresses showing NRVO actually happened.

## Gotchas
- Returning `std::move(v)` from a function is usually **worse** than `return v;` — it disables NRVO. Trust the compiler.
- After a move, the source vector is in a *valid but unspecified state*: you can destruct it or assign to it, nothing else without checking.
- "Move" is just a fancy way of saying "swap of pointers." It's not magic; it's a `noexcept` constructor that takes an rvalue reference.

## Run
    make 16.05
