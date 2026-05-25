# Chapter 22 — Move Semantics and Smart Pointers

Chapter 22 fixes the two biggest footguns in raw-pointer C++: leaks/double-frees and pointless copies. Smart pointers (RAII wrappers around `new`/`delete`) take care of ownership; move semantics (rvalue references + move ctor/assignment) lets the language hand off resources without copying them. By the end you can stop writing `delete` by hand and stop paying for copies you didn't want.

## Lessons

| # | Lesson |
|---|---|
| 22.01 | [Introduction to smart pointers and move semantics](22.01_intro_smart_pointers_and_move_semantics/NOTES.md) |
| 22.02 | [R-value references](22.02_rvalue_references/NOTES.md) |
| 22.03 | [Move constructors and move assignment](22.03_move_constructors_and_move_assignment/NOTES.md) |
| 22.04 | [`std::move`](22.04_std_move/NOTES.md) |
| 22.05 | [`std::unique_ptr`](22.05_std_unique_ptr/NOTES.md) |
| 22.06 | [`std::shared_ptr`](22.06_std_shared_ptr/NOTES.md) |
| 22.07 | [Circular dependency issues with `std::shared_ptr`, and `std::weak_ptr`](22.07_circular_dependency_and_weak_ptr/NOTES.md) |
| 22.x | [Summary & quiz](22.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear, but the conceptual jumps are uneven:

- **22.01 → 22.02** — 22.01 motivates everything with a leaky raw-pointer example and a sketch of a smart pointer; 22.02 is the language-feature foundation (rvalue refs / `&&`). Read them together.
- **22.03 → 22.04** — move ctor/assign is where move semantics actually shows up. `std::move` (22.04) is just a cast — easy to misuse if you skipped 22.03.
- **22.05 → 22.07** — unique → shared → weak in that order. Don't reach for `shared_ptr` until you've felt how restrictive (and how safe) `unique_ptr` is. `weak_ptr` only makes sense once you've hit a circular reference.
