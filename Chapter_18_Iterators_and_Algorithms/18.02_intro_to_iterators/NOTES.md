# 18.2 — Introduction to iterators

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-iterators/

## Why it matters
An iterator is the "pointer-like thing" that lets one piece of code — `std::sort`, `std::find`, a range-for — work on an array, a `std::vector`, a `std::list`, and a `std::map` without caring how they store their elements. Once you accept the four-operation interface (`*`, `++`, `==`/`!=`, copy), every algorithm in `<algorithm>` becomes the same shape.

## Key points
- **Iterator = abstract pointer**. For each container type, the standard library provides an iterator type that knows how to step through *that* container's storage. You use them through the same uniform syntax.
- **The interface**:
  - `*it` — dereference, yields the current element.
  - `++it` — advance to the next element.
  - `it == other`, `it != other` — compare. Use `!=` against `end()`, not `<` (not all iterator categories support ordering).
  - copy/assign — iterators are cheap value types.
- **`begin()` / `end()`**: `end()` is **one past the last element** — a sentinel, not a valid dereference. The half-open range `[begin, end)` is everywhere in C++.
- **Range-based `for`** is sugar: `for (auto x : c)` calls `c.begin()` / `c.end()` and `++` / `*` under the hood. Same machinery, less typing.
- **`const_iterator`** when you don't intend to write through it. `cbegin()` / `cend()` give you those directly.
- **Iterator invalidation**: mutating a container (e.g. `vector::push_back` causing reallocation, `vector::erase` shifting elements) can leave existing iterators pointing at stale memory — UB to dereference. Re-fetch from `begin()` / `end()` or use the iterator that mutating operations return.

## Code in this folder
- `main.cpp` — manual iterator walk over `std::vector` vs. the range-for that wraps it, plus a `const_iterator` example and an invalidation demo (commented; flips on by `#define`).

## Gotchas
- `*end()` is undefined behavior. `end()` is a fence post, not an element.
- Comparing iterators across different containers is undefined behavior.
- `auto it = v.begin()` followed by `v.push_back(x)` may invalidate `it`. After a structural modification, *re-fetch*.
- `++it` and `it++` both work; `++it` avoids one copy. Negligible for `int*`-shaped iterators, occasionally measurable for fat iterators (e.g. `std::map`).

## Run
    make 18.02
