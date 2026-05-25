# 24.3 — Order of construction of derived classes

> learncpp.com: https://www.learncpp.com/cpp-tutorial/order-of-construction-of-derived-classes/

## Why it matters
A derived object's base part *must* be a valid `Base` before any `Derived` member function runs — otherwise the derived constructor could call a base function that touches uninitialized state. The compiler enforces that by constructing the base first. Destruction reverses the order so a class never sees its base destroyed before itself.

## Key points
- Construction order: **base → derived**, then derived members in declaration order.
- Destruction order: exact reverse — **derived → base**.
- In a chain `A ← B ← C`, construction is `A, B, C`; destruction is `~C, ~B, ~A`.
- Multiple local objects: each one is fully constructed before the next starts. Then at end of scope, they're destroyed in **reverse order of definition**.
- This is why you can rely on base members being initialized inside a derived constructor body.

## Code in this folder
- `main.cpp` — three-level hierarchy `A ← B ← C` with traced ctors/dtors; also creates a stand-alone `A` to show inter-object destruction order.

## Gotchas
- The destruction reversal applies *within* an object (derived before base) **and** across objects in the same scope. Both happen.
- Don't put logic that depends on derived members into base constructors — at that point the derived part doesn't exist yet.

## Run
    make 24.03
