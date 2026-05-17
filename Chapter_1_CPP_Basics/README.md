# Chapter 1 — C++ Basics

Chapter 1 walks from "what is a statement" up to a small interactive program. By the end you can read a simple C++ file, explain every token in it, write your own variables, do I/O with `std::cin`/`std::cout`, and reason about why uninitialized variables are dangerous.

## Lessons

| # | Lesson |
|---|---|
| 1.01 | [Statements and the structure of a program](1.01_statements_and_structure/NOTES.md) |
| 1.02 | [Comments](1.02_comments/NOTES.md) |
| 1.03 | [Introduction to objects and variables](1.03_objects_and_variables/NOTES.md) |
| 1.04 | [Variable assignment and initialization](1.04_assignment_and_initialization/NOTES.md) |
| 1.05 | [Introduction to iostream: cout, cin, endl](1.05_intro_to_iostream/NOTES.md) |
| 1.06 | [Uninitialized variables and undefined behavior](1.06_uninitialized_variables_and_ub/NOTES.md) |
| 1.07 | [Keywords and naming identifiers](1.07_keywords_and_identifiers/NOTES.md) |
| 1.08 | [Whitespace and basic formatting](1.08_whitespace_and_formatting/NOTES.md) |
| 1.09 | [Introduction to literals and operators](1.09_literals_and_operators/NOTES.md) |
| 1.10 | [Introduction to expressions](1.10_expressions/NOTES.md) |
| 1.11 | [Developing your first program](1.11_first_program/NOTES.md) |
| 1.x  | [Summary & quiz](1.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear — each lesson is small and builds on the previous. A few points worth slowing down on:

- **1.04** — prefer brace-initialization (`int x{ 5 };`). This habit pays off for the entire rest of the book.
- **1.06** — uninitialized reads are *undefined behavior*, not "you get a zero." This is the first time UB shows up; it will keep coming.
- **1.10 → 1.11** — expressions are the building blocks; the final lesson stitches everything together into a real interactive program.
