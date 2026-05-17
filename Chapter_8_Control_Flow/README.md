# Chapter 8 — Control Flow

Chapter 8 is where straight-line programs end. You learn how to pick a branch (`if`, `switch`), repeat work (`while`, `do-while`, `for`), bail out of loops (`break`, `continue`), end the program early (`exit`, `abort`), and generate random numbers properly with `<random>`. By the end, the structure of a non-trivial program — the actual *flow* — is something you can read and write deliberately instead of guessing at.

## Lessons

| # | Lesson |
|---|---|
| 8.01 | [Control flow introduction](8.01_control_flow_introduction/NOTES.md) |
| 8.02 | [If statements and blocks](8.02_if_statements_and_blocks/NOTES.md) |
| 8.03 | [Common if statement problems](8.03_common_if_statement_problems/NOTES.md) |
| 8.04 | [Constexpr if statements](8.04_constexpr_if_statements/NOTES.md) |
| 8.05 | [Switch statement basics](8.05_switch_statement_basics/NOTES.md) |
| 8.06 | [Switch fallthrough and scoping](8.06_switch_fallthrough_and_scoping/NOTES.md) |
| 8.07 | [Goto statements](8.07_goto_statements/NOTES.md) |
| 8.08 | [Introduction to loops and while statements](8.08_intro_to_loops_and_while/NOTES.md) |
| 8.09 | [Do-while statements](8.09_do_while_statements/NOTES.md) |
| 8.10 | [For statements](8.10_for_statements/NOTES.md) |
| 8.11 | [Break and continue](8.11_break_and_continue/NOTES.md) |
| 8.12 | [Halts (exiting your program early)](8.12_halts/NOTES.md) |
| 8.13 | [Introduction to random number generation](8.13_intro_to_random_number_generation/NOTES.md) |
| 8.14 | [Generating random numbers using Mersenne Twister](8.14_mersenne_twister/NOTES.md) |
| 8.15 | [Global random numbers (Random.h)](8.15_global_random_numbers/NOTES.md) |
| 8.x  | [Summary & quiz](8.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear, but the chapter has three natural clusters:

- **8.01 → 8.07 — Selection.** `if`, `switch`, and the surprisingly subtle ways they break (dangling else, missing braces, fallthrough, `goto`). 8.04 (`if constexpr`) is the only forward-looking detour — templates make more sense of it later, but you can read it now.
- **8.08 → 8.12 — Iteration & flow control.** The four loop forms, then `break`/`continue`/`return`/`exit`. Most beginners trip on the loop-variable signedness issue in 8.10 and on `do-while`'s scoping in 8.09 — read those carefully.
- **8.13 → 8.15 — Random numbers.** The site introduces a `Random.h` header (its own wrapper around `<random>`). In this repo each lesson is **standalone**: every `main.cpp` uses `<random>` directly so you can build any lesson without copying a shared header. Same effect, no dependency.
