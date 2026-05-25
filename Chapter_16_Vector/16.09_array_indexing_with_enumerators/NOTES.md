# 16.9 — Array indexing and length using enumerators

> learncpp.com: https://www.learncpp.com/cpp-tutorial/array-indexing-and-length-using-enumerators/

## Why it matters
A vector indexed by raw integers — `inventory[2]` — tells the reader nothing. Was that arrows or torches? Naming positions with enumerators turns the code into documentation, and lets the compiler help you keep the count of items and the count of enumerator names in sync.

## Key points
- Define an unscoped enum (in a namespace, to avoid polluting global scope): `namespace Items { enum Type { health_potion, torch, arrow, max_items }; }`.
- Use it as an index: `inv[Items::torch]`. Unscoped enums convert to `int` implicitly — they work directly as subscripts.
- Use the **sentinel** enumerator (`max_items`) for length-related work: `inv.size() == Items::max_items` is a great `static_assert` / `assert`.
- **Prefer unscoped enums in a namespace** here. Scoped enums (`enum class`) don't implicitly convert to int — you'd need a cast at every subscript, defeating the purpose.
- The pattern scales to any "small fixed set of named slots": days of the week, character stats, board cells.

## Code in this folder
- `main.cpp` — `Items` namespace with the sentinel, vector built around it, both index loop and named access.

## Gotchas
- Don't forget the `max_items` sentinel. It's what protects you from quietly desynced vector size if you add a new enumerator.
- Unscoped enum + global scope = name pollution (`torch` floats free). Always wrap in a namespace.
- `static_assert(std::ssize(v) == max_items)` doesn't compile for `std::vector` (size isn't constexpr). Use a runtime `assert`, or switch to `std::array` if the size is fixed.

## Run
    make 16.09
