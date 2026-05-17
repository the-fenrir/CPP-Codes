# Chapter 3 — Debugging C++ Programs

Chapter 3 is about the part of programming nobody teaches you: making a wrong program right. It splits cleanly into three blocks — understanding what kinds of bugs exist, ad-hoc tactics (print statements, commenting out, logging), and using an actual debugger (stepping, breakpoints, watches, the call stack). The chapter is written around Visual Studio / Code::Blocks; for this repo's terminal + Makefile setup, the equivalent tool is `gdb` (Linux) or `lldb` (macOS), and the NOTES in each lesson translate the IDE workflow into those commands.

## Lessons

| # | Lesson |
|---|---|
| 3.01 | [Syntax and semantic errors](3.01_syntax_and_semantic_errors/NOTES.md) |
| 3.02 | [The debugging process](3.02_debugging_process/NOTES.md) |
| 3.03 | [A strategy for debugging](3.03_debugging_strategy/NOTES.md) |
| 3.04 | [Basic debugging tactics](3.04_basic_debugging_tactics/NOTES.md) |
| 3.05 | [More debugging tactics](3.05_more_debugging_tactics/NOTES.md) |
| 3.06 | [Using an integrated debugger: stepping](3.06_debugger_stepping/NOTES.md) |
| 3.07 | [Using an integrated debugger: running and breakpoints](3.07_debugger_running_and_breakpoints/NOTES.md) |
| 3.08 | [Using an integrated debugger: watching variables](3.08_debugger_watching_variables/NOTES.md) |
| 3.09 | [Using an integrated debugger: the call stack](3.09_debugger_call_stack/NOTES.md) |
| 3.10 | [Finding issues before they become problems](3.10_finding_issues_early/NOTES.md) |
| 3.x  | [Summary & quiz](3.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear, but the chapter is really two halves stitched together:

- **3.01 → 3.05** — the conceptual + ad-hoc-tactics half. You can (and will) ship code with nothing but these. 3.04's "comment out half the program" and 3.05's `std::cerr` + conditional-compilation logging are the techniques you'll reach for 90% of the time.
- **3.06 → 3.09** — the integrated-debugger half. Read these four as a unit: stepping (3.06) is useless without breakpoints (3.07), and watches (3.08) + call stack (3.09) are what make the debugger pay for itself on non-trivial bugs. In our terminal setup, that means `lldb` on macOS or `gdb` on Linux; the binaries this repo builds already have `-g` debug info, so `lldb build/3.06/main` just works.
- **3.10** is the "shift left" lesson — most of the chapter is reactive (something broke, now fix it); this one is the proactive flip side (compiler warnings, static analysis, defensive programming, unit tests).
