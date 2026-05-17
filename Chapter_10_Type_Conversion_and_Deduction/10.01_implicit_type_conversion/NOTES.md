# 10.1 — Implicit type conversion

> learncpp.com: https://www.learncpp.com/cpp-tutorial/implicit-type-conversion/

## Why it matters
C++ is statically typed, but real code mixes types constantly: `double x = 5;`, `if (ptr)`, `int n = some_short;`. The compiler patches the mismatch by inserting an **implicit conversion**. Most of the time it's harmless. Some of the time it silently throws away information. Knowing which is which is the entire point of the next four lessons.

## Key points
- A conversion produces a *new value* of the destination type from a value of the source type. The source object is unchanged.
- Implicit conversions are inserted by the compiler wherever a type mismatch is "fixable" — initialization, assignment, return, function arg, condition.
- The standard categorizes them into a few buckets, and the next lessons drill in:
  - **Numeric promotion** (10.02): safe, value-preserving widening (`short → int`, `float → double`).
  - **Numeric conversion** (10.03): everything else — may lose value or precision.
  - **Arithmetic conversion** (10.05): the rules that govern operands of `+ - * / %` etc.
- When **no legal conversion sequence** exists, you get a compile error. When one *does* exist but loses information, you usually get a warning at best — and that's the trap.

## Code in this folder
- `main.cpp` — shows several implicit conversions in action: init, assignment, return, argument passing, and a condition.

## Gotchas
- "Compiles cleanly" ≠ "preserves value." `int n = 3.9;` compiles (with warning) and stores `3`.
- Implicit conversions can chain — `char → int → double` happens in one step from the source code's point of view.
- Brace-initialization (`int n{ 3.9 };`) refuses narrowing conversions. That's the safety belt — see 10.04.

## Run
    make 10.01
