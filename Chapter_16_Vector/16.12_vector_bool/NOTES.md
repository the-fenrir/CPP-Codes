# 16.12 — std::vector&lt;bool&gt;

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdvector-bool/

## Why it matters
`std::vector<bool>` is the standard library's most famous mistake. It's *not* a vector of `bool` — it's a space-optimized bitset that pretends to be one, and the disguise leaks in surprising places. Knowing the trap is more important than knowing how to use it.

## Key points
- `std::vector<bool>` is a **specialization** that packs values into bits — one byte holds 8 booleans.
- `v[i]` does **not** return `bool&`. It returns a **proxy object** that emulates a reference to a bit. Most of the time, fine; sometimes, surprising.
- Consequences:
  - `auto x = v[0];` makes `x` a *proxy*, not a `bool`. Use `bool x = v[0];` to force a copy.
  - You **cannot** take `&v[0]` and pass it as `bool*` — there's no `bool` there.
  - It does not satisfy the C++ container requirements (no `operator&` for elements). Generic code may fail.
- **Recommended alternatives**:
  - `std::vector<char>` or `std::vector<std::uint8_t>` if you need a real array of true/false flags.
  - `std::bitset<N>` for a fixed-size bit array.
  - `std::vector<bool>` only when the space saving genuinely matters and you accept the proxy semantics.

## Code in this folder
- `main.cpp` — `vector<bool>` works fine *until* you reach for `auto` or `&`; demonstrates both.

## Gotchas
- "It worked in my last `vector<int>` code" doesn't carry over. The specialization is a different class.
- `vector<bool>` iteration with range-for **by value** works (`for (bool b : v)`). By reference *appears* to work (`for (auto& b : v)`) but you're holding the proxy, not a real bool.

## Run
    make 16.12
