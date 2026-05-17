# 13.6 — Scoped enumerations (`enum class`)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/scoped-enumerations-enum-classes/

## Why it matters
Unscoped enums have two problems: their enumerators leak into the enclosing scope, and they implicitly convert to `int`. Both bite in real codebases. `enum class` (a.k.a. scoped enumeration) fixes both, and is the **default choice** for any new enum in modern C++.

## Key points
- Syntax: `enum class Color { red, green, blue };`. Use `Color::red`, never bare `red`.
- **No implicit conversion to int.** `std::cout << Color::red;` is a compile error — you must `static_cast<int>(...)` if you want the integer. (Same fix as for printing: overload `operator<<`.)
- Comparing across types fails: `Color::red == Fruit::apple` is a compile error, even though they're both `0`. That's the type-safety win.
- Underlying type defaults to `int` for `enum class` (unlike unscoped enums, where it's implementation-defined). You can change it: `enum class Color : std::uint8_t { ... };`.
- **C++23**: `std::to_underlying(e)` is the idiomatic way to get the underlying integer. Pre-C++23 you write `static_cast<std::underlying_type_t<E>>(e)`.
- **`using enum`** (C++20): brings enumerators into the current scope inside a function or class, so you can write `red` instead of `Color::red` locally where it's clear.

## Code in this folder
- `main.cpp` — defines two scoped enums that would collide if unscoped; shows the compile error you avoid; demonstrates `using enum` and the underlying-type cast.

## Gotchas
- Mixing scoped enums with arithmetic still requires explicit casts. That's intentional — if you want a number, ask for one.
- `enum class` is not slower than `enum` — it's just a type-system change at compile time.

## Run
    make 13.06
