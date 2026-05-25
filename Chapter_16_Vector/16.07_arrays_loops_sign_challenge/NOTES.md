# 16.7 — Arrays, loops, and sign challenge solutions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/arrays-loops-and-sign-challenge-solutions/

## Why it matters
This lesson is the **answer key** to the unsigned-loop problem from 16.3. The language gives you several escape hatches; the goal here is to know which one to reach for, and why "just use `size_t`" isn't always the cleanest.

## Key points
Four practical solutions, in order of preference for everyday code:

1. **Range-based for loop** (16.8). When you don't actually need the index, this is the right answer — no indices, no conversions, no off-by-one.
2. **`std::size_t` loop**. Forward iteration when you do need the index. Avoid for reverse loops; use solution 3 there.
3. **`std::ssize` (C++20)**. Returns a *signed* size. Loop with `auto i = std::ssize(v) - 1; i >= 0; --i`. The cleanest signed-loop idiom.
4. **Cast at the boundary**. `const int n = static_cast<int>(v.size());` once, then loop with `int`. Verbose but explicit; useful in mixed-signedness code.

Anti-patterns:
- `for (size_t i = v.size() - 1; i >= 0; --i)` — infinite loop on unsigned.
- Disabling warnings instead of fixing the comparison.

## Code in this folder
- `main.cpp` — the same reverse-print done three legitimate ways.

## Gotchas
- Even with `std::ssize`, subscripting still wants `size_t` — so you may still cast inside the loop body.
- `auto` on `v.size() - 1` keeps the *unsigned* type. The fix is `std::ssize`, not `auto`.

## Run
    make 16.07
