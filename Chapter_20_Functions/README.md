# Chapter 20 — Functions

Chapter 20 finishes the story of functions: how they're laid out in memory (stack vs. heap), how to pass them around (function pointers), how to call themselves (recursion), how to take input from outside the program (command line args, ellipsis), and how to write them inline at the call site (lambdas + captures). By the end you can treat *functions as values* — store them, pass them, return them, and synthesize them on the fly.

## Lessons

| # | Lesson |
|---|---|
| 20.01 | [Function pointers](20.01_function_pointers/NOTES.md) |
| 20.02 | [The stack and the heap](20.02_stack_and_heap/NOTES.md) |
| 20.03 | [Recursion](20.03_recursion/NOTES.md) |
| 20.04 | [Command line arguments](20.04_command_line_arguments/NOTES.md) |
| 20.05 | [Ellipsis (and why to avoid them)](20.05_ellipsis/NOTES.md) |
| 20.06 | [Introduction to lambdas (anonymous functions)](20.06_intro_to_lambdas/NOTES.md) |
| 20.07 | [Lambda captures](20.07_lambda_captures/NOTES.md) |
| 20.x | [Summary & quiz](20.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear, but the chapter splits into three loosely-connected blocks:

- **20.01 → 20.02** — function pointers + memory layout. Knowing where a function *lives* makes "pointer to function" stop feeling exotic.
- **20.03 → 20.05** — control flow and I/O extensions: recursion, command line args, variadic ellipsis. 20.05 mainly exists to warn you off ellipsis; the modern replacements (variadic templates, `std::initializer_list`, `std::format`) are later.
- **20.06 → 20.07** — lambdas. This is the payoff: the language gives you a way to write small functions at the call site, and captures make them able to remember state. Everything in `<algorithm>` becomes much nicer once these click.
