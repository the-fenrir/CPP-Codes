# 8.8 — Introduction to loops and while statements

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-loops-and-while-statements/

## Why it matters
A *loop* repeats a block while a condition holds. `while` is the most general form — the condition is checked **before** each iteration, including the very first one, so a `while` may run zero times. That "zero times" property is the right default: it matches "for each thing in this collection, possibly empty" and "until this state is reached, which may already be reached." Other loop forms (`do-while`, `for`) are specialized cases.

## Key points
- Shape: `while (condition) statement;` — usually a `{}` block. Condition is converted to `bool`.
- Evaluation order each pass: **check condition → run body → check again**. If the condition is false the first time, the body never runs.
- Always make sure the body **changes** something the condition depends on, or use `break` from inside. Otherwise you have an infinite loop.
- `while (true) { ... if (done) break; }` is a legitimate pattern when the natural exit is mid-iteration (not before). Don't twist a condition into the head just to avoid it.
- Loop counters: prefer signed `int` unless you have a reason to use unsigned. Off-by-one bugs are rife — pick `< n` or `<= n - 1` deliberately and stick with one form.

## Code in this folder
- `main.cpp` — `while` counting up, `while` reading until a sentinel, and the "checked-zero-times" property demonstrated.

## Gotchas
- `while (i = 10)` instead of `while (i == 10)` — same assignment-vs-comparison trap as `if`.
- A semicolon after `while (cond);` makes the loop body empty — the loop runs to satisfaction with no body. Almost always a bug.
- Modifying the iteration variable inside the body in surprising ways (or modifying the collection you're iterating over) is how off-by-one and skipped-element bugs happen.

## Run
    make 8.08
