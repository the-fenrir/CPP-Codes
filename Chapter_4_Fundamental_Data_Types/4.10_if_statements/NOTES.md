# 4.10 — Introduction to if statements

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-if-statements/

## Why it matters
The `if` statement is the first piece of control flow you meet beyond "execute every line top to bottom." It's also where bugs love to hide — dangling-else, accidental assignment, brace-less branches that grow into multi-statement blocks.

## Key points
- Syntax: `if (condition) statement;` — optionally followed by `else statement;`. `condition` is a `bool` (or anything convertible to one: zero → `false`, non-zero → `true`).
- Chain conditions with `else if`. The chain short-circuits: the first matching branch runs, others are skipped.
- A branch may be a single statement *or* a compound `{ … }` block. **Always use braces.** A brace-less branch that grows into two statements has caused real CVEs (look up "goto fail").
- Functions returning `bool` plug straight into `if`: `if (isValid(x)) …`. Don't print the bool — use it.
- **Early return** pattern: `if (bad-case) return …;` at the top of a function reduces nesting.

## Code in this folder
- `main.cpp` — a small classification routine with `if`/`else if`/`else`, a non-boolean condition (`if (x)`), and an early-return helper.

## Gotchas
- `if (x = 0)` is assignment + condition — always false. `if (x == 0)` is the comparison.
- Dangling `else` binds to the nearest unbraced `if`. Brace consistently to remove the ambiguity entirely.

## Run
    make 4.10
