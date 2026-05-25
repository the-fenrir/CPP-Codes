# 16.6 — Arrays and loops

> learncpp.com: https://www.learncpp.com/cpp-tutorial/arrays-and-loops/

## Why it matters
Manually unrolling array access (`v[0]`, `v[1]`, …) doesn't scale and breaks at runtime sizes. The pairing of "array + loop" is *the* fundamental traversal pattern; every higher-level loop construct (range-for, algorithms) is shorthand for this.

## Key points
- The canonical traversal: `for (size_t i = 0; i < v.size(); ++i) use(v[i]);`.
- The loop's three jobs: **init**, **condition**, **iteration**. Index-based loops are necessary when you also need *i* (e.g., printing the index, comparing adjacent elements).
- Common patterns you should be able to write fluently:
  - **Sum** / **product** / **count-if**.
  - **Find the index** of the first matching element.
  - **Min / max** index and value.
  - **Pairwise** access: `v[i]` and `v[i+1]`, with condition `i + 1 < v.size()` to avoid stepping off the end.
- For "just touch every element," prefer **range-based for** (16.8). Use index loops when you need the index.

## Code in this folder
- `main.cpp` — sum, find-first, min-index, all written as classic index loops.

## Gotchas
- `i < v.size()`, never `i <= v.size()`. The valid range is `[0, size)`.
- For pairwise access, the loop bound shifts to `size - 1`. If `size` is 0 and unsigned, `size - 1` wraps — guard with `if (v.size() >= 2)`.

## Run
    make 16.06
