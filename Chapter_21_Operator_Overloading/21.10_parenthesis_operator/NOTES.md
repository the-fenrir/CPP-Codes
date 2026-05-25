# 21.10 — Overloading `operator()`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/overloading-the-parenthesis-operator/

## Why it matters
`operator()` is the "make my object callable" operator. An instance with `operator()` defined is called a **functor** (or function object). Two real uses:
1. **Stateful callable** — an object that behaves like a function but carries data with it (a counter, a comparator, a closure).
2. **Multi-argument indexing** — `m(i, j)` for a matrix; pre-C++23 this was the only clean way (subscript took one arg).

## Key points
- Must be a member function. Arbitrary parameter count and arbitrary return type — it's the most flexible operator in the language.
- Often paired with `const` if the call doesn't mutate state.
- The STL uses functors heavily: `std::sort(v.begin(), v.end(), MyComparator{});` — `MyComparator` is just a class with `operator()`.
- Lambdas are anonymous classes with `operator()`. Same shape, less typing.

## Code in this folder
- `main.cpp` — a `Matrix2x2` using `m(row, col)` and a `Counter` functor that remembers how many times it was called.

## Gotchas
- Don't reach for a functor when a lambda suffices. Functors are the right answer when you need *named*, *reusable*, or *type-traited* callables.
- A functor with mutable state must drop the `const` on `operator()` (or use `mutable` members). Caller-visible side effects from a callable are a usability tax — be deliberate.

## Run
    make 21.10
