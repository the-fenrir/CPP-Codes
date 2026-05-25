# 17.6 — `std::array` and enumerations

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdarray-and-enumerations/

## Why it matters
A common pattern: you have N named things (potions, suits, error codes) and want one or more parallel arrays of data — names, costs, weights. Indexing those arrays with an `int` literal is fragile and self-documenting only by comment. Indexing them with an enumerator (`Potion::healing`) gives you a name at the call site, a single source of truth for "how many," and a `static_assert`-able compile-time check that the arrays haven't drifted out of sync.

## Key points
- Use an *unscoped* `enum` (not `enum class`) inside a namespace so its enumerators implicitly convert to `int` for indexing: `costs[Potion::healing]`.
- Add a sentinel enumerator (often `max_X`) as the last entry. It auto-grows when you add a new value and gives you the array length: `constexpr std::array<int, Potion::max_potions> cost { ... };`.
- `static_assert(std::size(cost) == Potion::max_potions);` catches the moment someone adds an enumerator but forgets to extend the data array.
- For scoped enums (`enum class`), you need an explicit `static_cast<std::size_t>(rank)` or a helper conversion. Trades convenience for type safety.

## Code in this folder
- `main.cpp` — a `Potion` namespace with a `Type` enum and three parallel `constexpr std::array`s (name, cost, weight) indexed by enumerator. A `static_assert` guards array length.

## Gotchas
- Forget the `max_` sentinel and you'll hardcode `4` in five places. Add a potion, miss one, get UB.
- Unscoped enums inside a namespace are the trick — naked unscoped enums at file scope leak names. Scoped enums avoid the leak but lose implicit-to-int indexing.
- If you `static_cast` to a smaller type than `std::size_t` for indexing, you can get sign-conversion warnings. Cast to `std::size_t` directly.

## Run
    make 17.06
