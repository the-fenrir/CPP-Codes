# Chapter 2 — C++ Basics: Functions and Files

Chapter 2 introduces the two organizing tools every non-trivial C++ program leans on: **functions** (factor work into named, reusable units) and **files** (split a program across translation units that the linker stitches together). By the end you can write multi-file programs with headers, header guards, and namespaces, and reason about why each of those exists.

## Lessons

| # | Lesson |
|---|---|
| 2.01 | [Introduction to functions](2.01_intro_to_functions/NOTES.md) |
| 2.02 | [Function return values](2.02_function_return_values/NOTES.md) |
| 2.03 | [Void functions](2.03_void_functions/NOTES.md) |
| 2.04 | [Introduction to function parameters and arguments](2.04_parameters_and_arguments/NOTES.md) |
| 2.05 | [Introduction to local scope](2.05_local_scope/NOTES.md) |
| 2.06 | [Why functions are useful, and how to use them effectively](2.06_why_functions_are_useful/NOTES.md) |
| 2.07 | [Forward declarations and definitions](2.07_forward_declarations/NOTES.md) |
| 2.08 | [Programs with multiple code files](2.08_multiple_code_files/NOTES.md) |
| 2.09 | [Naming collisions and an introduction to namespaces](2.09_naming_collisions_and_namespaces/NOTES.md) |
| 2.10 | [Introduction to the preprocessor](2.10_preprocessor/NOTES.md) |
| 2.11 | [Header files](2.11_header_files/NOTES.md) |
| 2.12 | [Header guards](2.12_header_guards/NOTES.md) |
| 2.13 | [How to design your first programs](2.13_designing_your_first_programs/NOTES.md) |
| 2.x  | [Summary & quiz](2.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear. A few signposts:

- **2.01 → 2.04** — the function mechanics stack. Each lesson adds one piece (call, return, void, parameters); skipping ahead leaves gaps.
- **2.07 → 2.08 → 2.11 → 2.12** — the multi-file pipeline. Forward declarations explain *what* a header automates; headers explain *why* they're nicer; header guards explain the one rule headers can't break.
- **2.09** sits next to the preprocessor lessons because `using namespace std;` and `#include` together are responsible for most beginner naming surprises.
- **2.13** is meta — read it before starting any exercise that asks you to design something from scratch.
