# 18.1 — Sorting an array using selection sort

> learncpp.com: https://www.learncpp.com/cpp-tutorial/sorting-an-array-using-selection-sort/

## Why it matters
Sorting is the canonical "I could write this myself" task — and the canonical reason you shouldn't. Implementing selection sort once teaches you what `std::sort` is doing under the hood: scan-and-swap, an O(n²) operation that gets embarrassingly slow on big inputs. Once you've felt the cost, you stop reaching for hand-rolled loops and start reaching for `<algorithm>`.

## Key points
- **Selection sort algorithm**: for each index `i`, find the smallest element in `[i, n)` and swap it into position `i`. Outer loop runs `n-1` times (the last element falls into place for free).
- **`std::swap`** (from `<utility>`) exchanges two values — equivalent to a 3-line temp dance, but clearer at the call site.
- **Complexity**: O(n²) comparisons, O(n) swaps. Fine for ≤ ~100 elements; terrible for 100k.
- **`std::sort`** (from `<algorithm>`) is the production answer. Typically introsort: O(n log n), in-place, exploits whatever the implementation can — it'll always beat your hand-rolled selection sort.
- Bubble sort, insertion sort, etc. are other O(n²) sorts with the same lesson: educational, not for shipping.

## Code in this folder
- `main.cpp` — selection sort by hand on an `int` array, then the same array sorted by `std::sort`. Same result; one is one line.

## Gotchas
- Off-by-one in the inner loop: it must scan `[i+1, n)`, not `[i, n)`. Swapping with yourself is harmless but wastes work; reading past the end is undefined behavior.
- Don't use `<` to compare iterators in generic code. Selection sort on an array uses `int` indices, so it's fine — but the same algorithm rewritten for iterators needs `!=` (see 18.02).
- Re-rolling sort for "performance" almost always loses to `std::sort`. The standard library knows tricks your loop doesn't.

## Run
    make 18.01
