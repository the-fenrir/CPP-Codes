# 24.2 — Basic inheritance in C++

> learncpp.com: https://www.learncpp.com/cpp-tutorial/basic-inheritance-in-c/

## Why it matters
Once you write `class Derived : public Base`, the derived object physically *contains* a base subobject. Its layout, member visibility, and what the compiler synthesizes all flow from that fact. This lesson nails down the mechanics before the rest of the chapter pushes on them.

## Key points
- Syntax: `class Derived : public Base { ... };`. The `public` is the **inheritance mode** (covered fully in 24.05); use `public` unless you have a specific reason not to.
- A `Derived` object contains a `Base` subobject. From the derived side, base public members look like the derived's own public members.
- The derived class **does not inherit**: constructors, destructors, the assignment operator, friends. Member functions and data members it does inherit.
- A derived class can add its own members on top of the base — both data and functions.

## Code in this folder
- `main.cpp` — `Person` → `Employee`; `Employee` adds salary and a member function, then uses both base and derived members.

## Gotchas
- "Inherits everything" is wrong. Constructors aren't inherited (until you opt in with `using Base::Base;` — out of scope here).
- Derived can *access* inherited public members but can't access inherited `private` members of the base, even though they're physically part of the object. See 24.05.

## Run
    make 24.02
