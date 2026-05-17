# 2.6 — Why functions are useful, and how to use them effectively

> learncpp.com: https://www.learncpp.com/cpp-tutorial/why-functions-are-useful-and-how-to-use-them-effectively/

## Why it matters
Knowing the syntax of a function isn't the same as knowing when to write one. This lesson is the practical "when do I extract a function?" guide that determines whether your code stays readable past 100 lines.

## Key points
- **Organization**: name a chunk of logic with a verb phrase; the call site reads as a sentence.
- **Reusability**: write once, call many.
- **Testability**: small functions are unit-testable in isolation.
- **Abstraction**: callers care about *what* a function does, not *how*.
- Rules of thumb:
  - Code used more than once → function.
  - A block of code with a clear single responsibility → function, even if used once.
  - A function should typically fit on a screen. If it doesn't, it probably has more than one job.

## Code in this folder
- `main.cpp` — same calculation written inline and extracted into a function, so you can see the readability win.

## Gotchas
- Over-extraction: a function that's used once and consists of a single statement adds friction without buying anything.
- Functions that lie: `getX()` that also mutates state will mislead every caller. Name = what it does.
- A function with eight parameters is usually a struct trying to escape.

## Run
    make 2.06
