# 14.17 — Constexpr aggregates and classes

> learncpp.com: https://www.learncpp.com/cpp-tutorial/constexpr-aggregates-and-classes/

## Why it matters
`constexpr` lets values be computed at **compile time**. Extending that to classes means you can have rich types — `Point`, `Color`, `Vec3` — that act like literals: usable in array sizes, template parameters, `if constexpr` branches, with zero runtime cost. This is the seed of compile-time programming in modern C++.

## Key points
- An **aggregate** is a class with public data members, no user-declared/inherited constructors, no virtual functions, no base classes (with some C++20 relaxations). Aggregates with literal-typed members are automatically usable in constant expressions.
- A class can be made usable in constant expressions by marking its **constructor `constexpr`** (and other member functions you want to call at compile time).
- `constexpr` member functions are *implicitly* `const` in C++11/14 but **not** since C++14 — keep an eye on what version you're targeting. In C++20 most `constexpr` functions can do quite a lot (loops, allocation, etc.).
- A `constexpr` object: `constexpr Point p{ 1, 2 };` — must be constructed with arguments that are themselves constant expressions.
- Pairs nicely with `static_assert` for compile-time tests.

## Code in this folder
- `main.cpp` — a constexpr `Point` used in a `static_assert` and as a non-type template-like context.

## Gotchas
- A `constexpr` constructor doesn't *force* compile-time construction — it only *allows* it. Whether it's actually evaluated at compile time depends on the use site.
- Throwing inside a `constexpr` function makes it non-evaluable at compile time (the path that throws does). Compilers handle this gracefully but it surprises people.

## Run
    make 14.17
