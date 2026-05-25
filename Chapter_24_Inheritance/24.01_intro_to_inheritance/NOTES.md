# 24.1 — Introduction to inheritance

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-inheritance/

## Why it matters
Composition models "has-a": a `Car` has an `Engine`. Inheritance models "is-a": a `SportsCar` *is a* `Car`. When two types share a real conceptual category (and an interface), inheritance lets the derived one acquire the base's members for free — no copy-paste. Picking inheritance vs. composition is the load-bearing design decision of this chapter; get the relationship wrong and you'll fight the type system forever.

## Key points
- **Inheritance** = an "is-a" relationship between classes. Derived class acquires the base's members.
- Terminology: **base** (a.k.a. parent, superclass) and **derived** (a.k.a. child, subclass).
- A class can serve as base for many derived classes, and a derived class can itself be a base — building **inheritance hierarchies / trees**.
- Inheritance is for *categorization*. `Banana` is-a `Fruit`. `Engine` is *not* a `Car` — that's composition.
- "Reuse" is a side effect, not the goal. If two types only share *implementation*, prefer composition or a free function over inheritance.

## Code in this folder
- `main.cpp` — small `Person` → `BaseballPlayer` hierarchy; shows that the derived type silently picks up base members.

## Gotchas
- Don't model "X uses fields from Y" as inheritance. Inheritance is about *being a kind of* Y, not *needing a* Y.
- Once a class has derived classes, changing its public interface breaks every descendant. Bases are commitments.

## Run
    make 24.01
