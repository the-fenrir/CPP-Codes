# 24.7 — Calling inherited functions and overriding behavior

> learncpp.com: https://www.learncpp.com/cpp-tutorial/calling-inherited-functions-and-overriding-behavior/

## Why it matters
"Override" (in the non-virtual sense covered here) means a derived class redeclares a base function with the same name, shadowing the base version when called on a `Derived`. Often you want the derived version to *extend* the base — log first, then do whatever the base did. The mechanic for that is `Base::funcName()`.

## Key points
- Redeclaring a function in a derived class hides the base version when calling through `Derived`. The base function still exists; it's just not the one found first by name lookup.
- To reuse the base's behavior inside the derived version, call it with the qualified name: `Base::identify();`.
- A bare `identify()` inside `Derived::identify()` calls itself → infinite recursion. Always qualify the parent call.
- This is *static* override (non-`virtual`). Calling through a `Base*` will still pick the base version — virtual functions, which fix that, come in chapter 25.

## Code in this folder
- `main.cpp` — `Base::identify()` prints a base line. `Derived::identify()` calls `Base::identify()` first, then appends its own line.

## Gotchas
- Without the `Base::` prefix you have a stack overflow waiting to happen.
- Overriding here is **non-polymorphic**. Through a `Base*`, you'd get the base implementation. If you actually want polymorphic dispatch, mark the base function `virtual` (chapter 25).

## Run
    make 24.07
