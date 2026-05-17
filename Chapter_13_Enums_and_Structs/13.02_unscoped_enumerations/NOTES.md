# 13.2 — Unscoped enumerations

> learncpp.com: https://www.learncpp.com/cpp-tutorial/unscoped-enumerations/

## Why it matters
"States" should not be magic numbers. `if (status == 2)` is unreadable and unsafe — somebody else will write `if (status == 3)` for the same state. An enumeration gives each state a *name* and a *type*, so the compiler can keep them straight.

## Key points
- `enum Color { red, green, blue };` defines a new type `Color` with three **enumerators**. Each is implicitly `0, 1, 2, ...` from left to right.
- You can fix any enumerator value: `enum HttpStatus { ok = 200, notFound = 404 };`. Subsequent enumerators count from the last one.
- Enumerators of an *unscoped* enum **leak into the enclosing scope** — `red` is usable bare wherever the enum is visible. That's the source of name collisions and the reason scoped enums (13.6) exist.
- Place enum definitions in a header so multiple TUs can share them. ODR allows identical type definitions.
- Don't put unscoped enums at the global scope if you can avoid it — wrap them in a namespace to isolate the enumerator names.

## Code in this folder
- `main.cpp` — defines a `MonsterType` enum, shows enumerator naming, custom values, and namespace wrapping.

## Gotchas
- `enum Color { red };` and `enum Fruit { apple, red };` collide — `red` is in scope twice.
- You can't have two enumerators with the same name in the same scope, even across two unrelated enums.
- An enumerator's underlying integer is an *implementation detail*; don't rely on a specific value unless you fixed it explicitly.

## Run
    make 13.02
