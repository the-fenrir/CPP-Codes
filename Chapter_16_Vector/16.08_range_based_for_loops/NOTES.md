# 16.8 — Range-based for loops (for-each)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/range-based-for-loops-for-each/

## Why it matters
Most loops just say "do something to each element." The range-based for says that *directly*, without indices, off-by-ones, or signed/unsigned dances. It's the loop you'll write 90% of the time.

## Key points
- Syntax: `for (T x : v) { ... }`. Iterates left-to-right over every element.
- **By value** (`for (int x : v)`) copies each element — fine for cheap types, wasteful for heavy ones.
- **By const reference** (`for (const auto& x : v)`) — the default for read-only access; no copy.
- **By reference** (`for (auto& x : v)`) — when you intend to mutate.
- Use `auto` for the loop variable to avoid spelling the element type twice.
- Works for any range: `std::vector`, `std::array`, `std::string`, C arrays, `std::map` (yields pairs), …
- **Limitations**: you don't get the index. If you need it, use an index loop or `enumerate` (C++23) / a parallel counter.

## Code in this folder
- `main.cpp` — by-value vs. by-const-ref vs. by-ref, plus iterating a `std::string` and a vector-of-strings.

## Gotchas
- `for (auto x : v)` on `std::vector<std::string>` copies every string. Make it `const auto&`.
- Modifying the vector's structure (insert/erase) inside a range-for **invalidates the iteration**. Don't.
- The type after `for (` is the *element* type, not `std::vector<T>`. Beginners sometimes write `for (std::vector<int> x : v)`.

## Run
    make 16.08
