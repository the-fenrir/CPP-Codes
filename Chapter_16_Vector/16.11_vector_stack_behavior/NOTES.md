# 16.11 — std::vector and stack behavior

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdvector-and-stack-behavior/

## Why it matters
`std::vector` does double duty: it's an array *and* a perfectly good stack. The `push_back / back / pop_back` trio is one of the most-used APIs in real C++ code (parsers, DFS, undo buffers, anywhere you'd reach for "LIFO").

## Key points
- **`push_back(x)`** — append `x` to the end. Amortized O(1).
- **`emplace_back(args...)`** — construct in place from the args, skipping a temporary. Identical performance for trivially-constructible types; matters for heavy ones.
- **`back()`** — reference to the last element. UB if empty.
- **`pop_back()`** — remove the last element. Returns void (so save `back()` first if you want it). UB if empty.
- **`empty()`** — `true` iff `size() == 0`.
- The stack idiom: `vec.push_back(x); ... auto top = vec.back(); vec.pop_back();`.
- If you literally want a stack-only interface, `std::stack<T>` wraps a vector and hides the array-ish methods.

## Code in this folder
- `main.cpp` — paren-matching using a vector as a stack.

## Gotchas
- `pop_back()` on an empty vector is UB, not an exception. Always check `!empty()` first (or use `at()`-style sentinel logic).
- A reference returned by `back()` is invalidated by any subsequent `push_back` that triggers reallocation. Don't hold it across pushes.
- `emplace_back` is *not* always faster than `push_back` — for fundamental types, the compiler generates identical code. Use it where the constructor takes multiple args.

## Run
    make 16.11
