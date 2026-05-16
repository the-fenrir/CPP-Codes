# 14.1 — Introduction to object-oriented programming

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-object-oriented-programming/

## Why it matters
Procedural code separates **data** (variables) from **behavior** (functions that operate on it). That separation rots: as a program grows, "which functions are safe to call on this struct, and in what order?" stops being knowable. OOP bundles data + the functions that operate on it into one type, so the object enforces its own rules. This is the conceptual seed for everything in chapters 14–15.

## Key points
- **Object** = data + functions that act on that data, packaged together.
- **Class** = the blueprint; **object** = an instance of that blueprint.
- Procedural style: `printEmployee(e)`. Object style: `e.print()`. Same effect; the object form scopes behavior to the type that owns it.
- Four pillars typically named: encapsulation, inheritance, polymorphism, abstraction. Chapter 14–15 are mostly about **encapsulation**.
- OOP is a tool, not a religion. C++ supports both styles; pick the one that makes a given piece of code clearer.

## Code in this folder
- `main.cpp` — same task done procedurally and OO-style, side by side.

## Gotchas
- "Object-oriented" ≠ "good code." Wrapping everything in a class with getters/setters is not encapsulation — it's busywork.
- Don't reach for inheritance just because OOP says you can. Composition (a class containing other class instances) is the default, inheritance the exception.

## Run
    make 14.01
