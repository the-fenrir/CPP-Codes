# 8.1 — Control flow introduction

> learncpp.com: https://www.learncpp.com/cpp-tutorial/control-flow-introduction/

## Why it matters
By default a C++ program runs **top to bottom, one statement at a time** — straight-line execution. That's enough for trivial programs and nothing else. Real programs need to pick branches based on data ("is the user logged in?"), repeat work ("for every row in the file"), and bail out of work that turned out wrong. Everything in chapter 8 is about *bending* that default execution path on purpose. The vocabulary the rest of the chapter uses — *condition*, *branch*, *iteration*, *halt* — gets named here.

## Key points
- **Straight-line program**: each statement executes exactly once in source order. No `if`, no loops, no calls that change the path.
- A **control flow statement** is one that can cause the next statement executed to be somewhere other than the next line of source. C++ has a handful: `if`, `switch`, `for`, `while`, `do`, `break`, `continue`, `return`, `goto`, plus exception throws and `[[noreturn]]` halts.
- They fall into four buckets used through the chapter:
  - **Conditional branches** — `if`, `switch`. Pick at most one of N paths.
  - **Jumps** — `goto`, function calls, `return`. Unconditionally go somewhere.
  - **Loops** — `for`, `while`, `do-while`. Repeat a block while a condition holds.
  - **Halts** — `std::exit`, `std::abort`. End the program early.
- **Branch coverage** matters: testing only the "happy path" misses bugs that live in the *other* branch. Every `if`/`else`, every `case`, every loop's enter/skip behavior is a path you should walk through deliberately.

## Code in this folder
- `main.cpp` — a single tiny program demonstrating each of the four buckets so you can compare them side by side.

## Gotchas
- "Control flow statement" ≠ "statement that has side effects." A function call without `return` is *not* a control flow statement; a `return` is. The distinction matters when reasoning about which line executes next.
- Adding a `return` mid-function or an `exit()` deep in a helper makes the function harder to reason about — every later line silently becomes conditional. Use them, but sparingly, with a clear reason.

## Run
    make 8.01
