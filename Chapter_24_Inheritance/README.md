# Chapter 24 — Inheritance

Chapter 24 covers inheritance: how one class can derive from another and reuse its members. By the end you understand how derived objects are constructed, how access specifiers and inheritance mode interact, when to call vs. override vs. hide a base function, and why multiple inheritance is a tool of last resort.

## Lessons

| # | Lesson |
|---|---|
| 24.01 | [Introduction to inheritance](24.01_intro_to_inheritance/NOTES.md) |
| 24.02 | [Basic inheritance in C++](24.02_basic_inheritance/NOTES.md) |
| 24.03 | [Order of construction of derived classes](24.03_order_of_construction/NOTES.md) |
| 24.04 | [Constructors and initialization of derived classes](24.04_constructors_and_init_of_derived/NOTES.md) |
| 24.05 | [Inheritance and access specifiers](24.05_inheritance_and_access_specifiers/NOTES.md) |
| 24.06 | [Adding new functionality to a derived class](24.06_adding_new_functionality/NOTES.md) |
| 24.07 | [Calling inherited functions and overriding behavior](24.07_calling_inherited_and_overriding/NOTES.md) |
| 24.08 | [Hiding inherited functionality](24.08_hiding_inherited_functionality/NOTES.md) |
| 24.09 | [Multiple inheritance](24.09_multiple_inheritance/NOTES.md) |
| 24.x  | [Summary & quiz](24.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear. A few spots that bite:

- **24.03 → 24.04** — construction order is what makes the initializer list rules in 24.04 make sense. Read them together.
- **24.05** — the interaction of member access (`public`/`protected`/`private`) with inheritance mode (`public`/`protected`/`private`) is a table you should be able to redraw on demand.
- **24.07 → 24.08** — "override" vs. "hide" looks similar from the call site but behaves very differently. Be deliberate about which one you're doing.
- **24.09** — multiple inheritance is in the language; you should know it exists, but reach for composition or interface-only base classes first.
