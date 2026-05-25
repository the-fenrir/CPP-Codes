# 18.3 — Introduction to standard library algorithms

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-standard-library-algorithms/

## Why it matters
`<algorithm>` is the payoff for understanding iterators. Almost every loop you'd write — find this, count those, transform each, sort the lot — already exists, debugged, optimized, and named. Reading `std::find_if(v.begin(), v.end(), is_even)` is faster than reading the equivalent four-line loop, and the name encodes intent the loop can only hint at.

## Key points
- **Three families** of algorithms:
  - **Inspectors** — look at data: `std::find`, `std::find_if`, `std::count`, `std::count_if`, `std::all_of`, `std::any_of`.
  - **Mutators** — change data: `std::sort`, `std::reverse`, `std::shuffle`, `std::fill`.
  - **Facilitators** — produce a result: `std::for_each`, `std::transform`, `std::accumulate` (in `<numeric>`).
- **Common signature**: `algo(first, last, ...)` — a half-open range `[first, last)` plus extras (value, predicate, comparator, output iterator).
- **Predicates** are anything callable returning `bool`: free functions, function objects, **lambdas**. Lambdas are the everyday choice: `[](int x){ return x % 2 == 0; }`.
- **Custom comparators** for `std::sort`: `std::sort(v.begin(), v.end(), std::greater<>{})` for descending; pass a lambda for arbitrary order.
- **Return values matter**: `std::find` returns an iterator — `== end()` means "not found." Don't dereference a not-found iterator.
- **C++20 ranges** (`std::ranges::sort(v)`) drop the `.begin()/.end()` boilerplate. Same algorithms, cleaner call sites.
- **Why prefer algorithms over hand loops**: name encodes intent, fewer off-by-ones, parallelization hooks (`std::execution::par`), maintainers don't have to re-read your loop body.

## Code in this folder
- `main.cpp` — small tour: `std::find`, `std::find_if` with a lambda, `std::count_if`, `std::sort` with a custom comparator, `std::for_each`, and the C++20 `std::ranges::sort` equivalent.

## Gotchas
- `std::find(...)` returning `end()` is the "not found" signal. Always compare against `end()` before dereferencing.
- `std::for_each` is not always clearer than a range-for. Reach for it when you already have a named function or want a parallel execution policy.
- `std::remove` / `std::remove_if` don't remove — they shuffle "kept" elements forward and return the new logical end. You need the **erase-remove idiom**: `v.erase(std::remove_if(v.begin(), v.end(), pred), v.end());` (or `std::erase_if(v, pred)` in C++20).
- `std::sort` requires random-access iterators — works on `vector`, `array`, `deque`, raw arrays; **not** on `std::list` (use `list::sort()`).

## Run
    make 18.03
