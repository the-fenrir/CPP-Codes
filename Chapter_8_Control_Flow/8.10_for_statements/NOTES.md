# 8.10 — For statements

> learncpp.com: https://www.learncpp.com/cpp-tutorial/for-statements/

## Why it matters
`for` is `while` with the three boilerplate parts of a counter loop — *init*, *condition*, *step* — collected on one line. That collocation matters: a reader sees what bounds the loop is supposed to enforce without scanning the body. Use `for` exactly when those three parts are simple expressions. When the iteration logic gets complicated, fall back to `while` so the reader doesn't have to parse a stuffed header.

C++11 also gives us **range-based for** — `for (auto& x : container)` — which is the right tool whenever you don't actually need the index, because it can't go out of bounds.

## Key points
- Shape: `for (init; condition; step) statement;`
  - **init** runs once before the loop. Usually declares the counter: `int i = 0`.
  - **condition** is checked before each iteration. Loop exits when false. Empty == always true.
  - **step** runs after each iteration (before the next condition check). Usually `++i`.
- Any of the three can be omitted. `for (;;)` is the canonical infinite loop.
- The counter is **scoped to the loop**. It doesn't leak into the surrounding function — good. Don't declare it outside unless you specifically need it after.
- Prefer **signed** counters (`int`) unless you're iterating an unsigned-sized container. Comparing signed and unsigned (`int i < vec.size()`) is the most common loop warning you'll see.
- **Range-based for** for traversal: `for (const auto& e : v)` for read-only, `for (auto& e : v)` for in-place mutation. Use it whenever you don't need the index.

## Code in this folder
- `main.cpp` — a counting `for`, the equivalent rewritten as `while` (so you can see what `for` collapses), a range-based `for`, and an infinite `for(;;)` with a `break`.

## Gotchas
- **Off-by-one.** `i < n` (n iterations) vs. `i <= n` (n+1 iterations). Pick one and stay consistent.
- **Modifying the counter inside the body** while the step does its own thing is a maintenance nightmare. Don't.
- **Empty step + body that modifies the counter** is legal but reads like a riddle. Either keep the step or just use `while`.
- Range-based for over a temporary container is fine; range-based for over `for (auto x : getVec())` *copies each element* — use `const auto&` to avoid the copies.

## Run
    make 8.10
