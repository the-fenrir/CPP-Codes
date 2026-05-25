# Chapter 21 — Operator Overloading

Chapter 21 teaches you to make your own types interact with the built-in operator syntax (`a + b`, `std::cout << x`, `a[i]`, `f(x)`). The hard parts are not "what does `operator+` look like" but rather: when do you make it a member vs. a friend vs. a free function, how do you survive shallow-copy bugs once your class owns memory, and what does the `operator=` self-assignment dance actually buy you.

## Lessons

| # | Lesson |
|---|---|
| 21.01 | [Introduction to operator overloading](21.01_intro_to_operator_overloading/NOTES.md) |
| 21.02 | [Overloading the arithmetic operators using friend functions](21.02_arithmetic_via_friend_functions/NOTES.md) |
| 21.03 | [Overloading operators using normal functions](21.03_overloading_via_normal_functions/NOTES.md) |
| 21.04 | [Overloading the I/O operators](21.04_overloading_io_operators/NOTES.md) |
| 21.05 | [Overloading operators using member functions](21.05_overloading_via_member_functions/NOTES.md) |
| 21.06 | [Overloading unary operators `+`, `-`, and `!`](21.06_unary_operators/NOTES.md) |
| 21.07 | [Overloading the comparison operators](21.07_comparison_operators/NOTES.md) |
| 21.08 | [Overloading the increment and decrement operators](21.08_increment_decrement/NOTES.md) |
| 21.09 | [Overloading the subscript operator](21.09_subscript_operator/NOTES.md) |
| 21.10 | [Overloading the parenthesis operator](21.10_parenthesis_operator/NOTES.md) |
| 21.11 | [Overloading typecasts](21.11_typecasts/NOTES.md) |
| 21.12 | [Overloading the assignment operator](21.12_assignment_operator/NOTES.md) |
| 21.13 | [Shallow vs. deep copying](21.13_shallow_vs_deep_copy/NOTES.md) |
| 21.14 | [Overloading operators and function templates](21.14_overloading_and_templates/NOTES.md) |
| 21.x  | [Summary & quiz](21.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear. A few sequencing notes:

- **21.01 → 21.05** is one continuous argument about *where* an overload should live (friend, free function, member). Read them as a unit; the conclusion is "use the form with the fewest privileges that still works."
- **21.12 → 21.13** must be read together. Assignment in isolation is fine; assignment on a class that owns a raw pointer is where the shallow-copy crater happens. 21.13's lesson is really "or just use RAII / smart pointers and skip the whole thing."
- **21.07 / 21.08** are where `<=>` (C++20) replaces a wall of boilerplate — note where the chapter still uses pre-C++20 idioms and where you'd default-spaceship instead.
