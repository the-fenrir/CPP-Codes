# 14.12 — Delegating constructors

> learncpp.com: https://www.learncpp.com/cpp-tutorial/delegating-constructors/

## Why it matters
When you have several constructors, they usually share setup logic. Copy-pasting that logic into each one is the obvious wrong answer. **Delegating constructors** let one constructor call another, so a "small" constructor can forward to the "fat" one with sensible defaults. The setup logic lives in exactly one place.

## Key points
- Syntax: in the initializer list, call another constructor of *the same class*: `Foo() : Foo{ 0, 0 } {}`.
- Once you delegate, you may **not** also initialize other members in that initializer list — pick one.
- Delegation is a call, not inheritance. The delegated-to constructor runs to completion first, then any body code runs.
- Don't create a cycle (`A() : A() {}`) — infinite recursion, undefined behavior; some compilers warn.
- Often combined with default arguments (14.11). Pick the style that's clearer per class.

## Code in this folder
- `main.cpp` — `Rectangle` with three constructors: full, square, default — all routed through one implementation.

## Gotchas
- Initializer list rule: with delegation you can't also list members. Move any per-constructor member init into the target constructor or into default member initializers.
- Order of member init still follows declaration order — the delegated-to constructor doesn't change that.

## Run
    make 14.12
