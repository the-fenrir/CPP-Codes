# 7.1 — Compound statements (blocks)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/compound-statements-blocks/

## Why it matters
A **block** is `{ ... }` treated as one statement. Blocks introduce a new scope: names declared inside are invisible outside. This is the simplest scoping primitive in C++ and the basis for everything in 7.3 (local variables) and 7.5 (shadowing). Get this right and the rest of the chapter is just elaboration.

## Key points
- Any `{ ... }` is a compound statement; it can appear anywhere a single statement can.
- Each block opens a nested scope; names declared inside die at the closing `}`.
- A block inside a block can declare a name that *hides* an outer name with the same identifier (covered in 7.5).
- Nesting depth has a practical ceiling (~3 levels). Deeper nesting is a refactor smell.
- The body of a function is itself a block — the **function body block**.

## Code in this folder
- `main.cpp` — nested blocks, a name declared in an inner block invisible outside, and a missing-block bug (the dangling `if` from the chapter quiz Q1).

## Gotchas
- `if (cond) stmt1; stmt2;` — only `stmt1` is the body of the `if`; `stmt2` runs unconditionally. Always use `{ }` for non-trivial bodies.
- Re-using the same identifier in an inner block compiles and shadows. The compiler will not warn unless you ask (`-Wshadow`).

## Run
    make 7.01
