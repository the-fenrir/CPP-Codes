# Chapter 14 — Introduction to Classes

Chapter 14 introduces object-oriented programming in C++: classes, member functions, access control, encapsulation, and constructors. By the end you can model data + behavior together, decide what to expose vs. hide, and reliably initialize objects.

## Lessons

| # | Lesson |
|---|---|
| 14.01 | [Introduction to OOP](14.01_intro_to_oop/NOTES.md) |
| 14.02 | [Introduction to classes](14.02_intro_to_classes/NOTES.md) |
| 14.03 | [Member functions](14.03_member_functions/NOTES.md) |
| 14.04 | [Const class objects & const member functions](14.04_const_objects_and_const_members/NOTES.md) |
| 14.05 | [Public, private & access specifiers](14.05_access_specifiers/NOTES.md) |
| 14.06 | [Access functions](14.06_access_functions/NOTES.md) |
| 14.07 | [Member functions returning references to data members](14.07_returning_refs_to_members/NOTES.md) |
| 14.08 | [The benefits of data hiding (encapsulation)](14.08_encapsulation_benefits/NOTES.md) |
| 14.09 | [Introduction to constructors](14.09_constructors/NOTES.md) |
| 14.10 | [Constructor member initializer lists](14.10_member_initializer_lists/NOTES.md) |
| 14.11 | [Default constructors & default arguments](14.11_default_constructors/NOTES.md) |
| 14.12 | [Delegating constructors](14.12_delegating_constructors/NOTES.md) |
| 14.13 | [Temporary class objects](14.13_temporary_objects/NOTES.md) |
| 14.14 | [Introduction to the copy constructor](14.14_copy_constructor/NOTES.md) |
| 14.15 | [Class initialization and copy elision](14.15_copy_elision/NOTES.md) |
| 14.16 | [Converting constructors & the `explicit` keyword](14.16_converting_constructors_explicit/NOTES.md) |
| 14.17 | [Constexpr aggregates and classes](14.17_constexpr_aggregates_and_classes/NOTES.md) |
| 14.x | [Summary & quiz](14.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear — every lesson builds on the previous one. Pay extra attention at:

- **14.05 → 14.08** — public/private, access functions, the encapsulation argument all interlock. Don't skip 14.07; returning refs to members is a real footgun.
- **14.09 → 14.12** — the constructor sequence is the densest part of the chapter. Initializer lists (14.10) is where most beginners get hurt.
- **14.14 → 14.15** — the copy constructor only really makes sense once you understand copy elision; read them as a pair.
