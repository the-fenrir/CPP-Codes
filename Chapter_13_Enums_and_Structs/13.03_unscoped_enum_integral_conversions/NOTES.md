# 13.3 — Unscoped enumerator integral conversions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/unscoped-enumeration-input-and-output/

## Why it matters
Unscoped enums are "almost integers." That's both the convenience (they print, they compare, they index) and the trap (you can do arithmetic on them and the compiler won't stop you). Knowing exactly which conversion is implicit and which isn't is the foundation for choosing between unscoped enums and `enum class`.

## Key points
- **Enum → int is implicit.** `std::cout << red;` works; it prints the underlying integer.
- **Int → enum is NOT implicit.** `Color c = 1;` is a compile error. You need a cast: `Color c = static_cast<Color>(1);`. C++17 also allows list-init from an integer for fixed-base enums: `Color c{ 1 };`.
- Each enum has an **underlying type** — the integer the values are stored in. Default is implementation-defined (must hold all enumerators). You can fix it: `enum Color : std::int8_t { ... };`.
- Fixing the underlying type lets you forward-declare the enum.
- `std::cin >> e;` won't work for an unscoped enum without help — you read into an `int` (or the underlying type) and cast.

## Code in this folder
- `main.cpp` — implicit enum→int, explicit int→enum cast, fixed underlying type, reading an enum from `std::cin` via an int.

## Gotchas
- `Color c = red + 1;` *compiles* (both sides promote to `int`, result is `int`, assigned-back fails... unless the enum is fixed-base, in which case rules differ). Don't do arithmetic on enums — use a cast if you really mean it.
- Casting an out-of-range int to an enum has implementation-defined behavior. Validate the int first.

## Run
    make 13.03
