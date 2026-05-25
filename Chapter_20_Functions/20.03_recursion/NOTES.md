# 20.3 — Recursion

> learncpp.com: https://www.learncpp.com/cpp-tutorial/recursion/

## Why it matters
A recursive function calls itself on a smaller version of the problem until it hits a base case. It's the natural fit for inherently nested structures — trees, divide-and-conquer search, parsing — and an exercise in stack discipline: every level of recursion costs one stack frame.

## Key points
- Two ingredients, both mandatory:
  1. **Base case(s)** — input small enough to answer directly, *without* recursing.
  2. **Recursive case(s)** — call yourself on strictly smaller input, then combine.
- Missing or unreachable base case ⇒ infinite recursion ⇒ stack overflow.
- **Memoization**: cache results for inputs you've already solved. Turns exponential trees (naive Fibonacci) into linear walks.
- Any recursion can be rewritten iteratively (with an explicit stack/loop). Sometimes iteration is clearer (factorials, sums); sometimes recursion is (tree traversals, recursive descent parsing).
- **Tail recursion** = the recursive call is the *last* thing the function does. Some compilers optimize it into a loop (no frame growth); MSVC generally doesn't. Don't rely on it for correctness on deep inputs — prefer iteration if depth is unbounded.

## Code in this folder
- `main.cpp` — factorial (clean base case), Fibonacci naive vs. memoized (why caching matters), sum-of-digits (recursion that mirrors the data shape).

## Gotchas
- Negative or otherwise out-of-range arguments are an easy way to skip the base case — defensively bound the input or assert it.
- "Small" stack frames still cost: ~10⁵ levels is plenty on a default Linux stack, but ~10⁶ usually overflows. If depth scales with input size, use a loop.
- Don't return a reference to a local from a recursive function — same trap as 20.2, just easier to forget when you're focused on the algorithm.

## Run
    make 20.03
