# 3.1 — Syntax and semantic errors

> learncpp.com: https://www.learncpp.com/cpp-tutorial/syntax-and-semantic-errors/

## Why it matters
Every bug you ever write falls into one of two buckets, and the bucket determines who finds it. **Syntax errors** are grammar violations — the compiler refuses the program and tells you the line. **Semantic errors** are valid C++ that does the wrong thing — the compiler is happy, the program runs, and a human has to notice. Naming the two categories early matters because the rest of the chapter is really just "how to hunt semantic errors," since syntax errors hunt themselves.

## Key points
- **Syntax error**: violates the language grammar. Missing `;`, unmatched `}`, typo'd keyword. Compiler catches 100% of them — the error message *is* the diagnosis.
- **Semantic error**: legal code with wrong meaning. `i <= n` instead of `i < n`, `+` where `-` was meant, integer division when floating-point was wanted. Compiler can't catch these — only tests or a user can.
- Some semantic errors *are* surfaced by the compiler as warnings (`-Wall -Wextra`): uninitialized variable, unused result, signed/unsigned mismatch. Always compile with warnings on and treat them as errors.
- Undefined behavior is a special case of semantic error where the *symptom* is non-deterministic: works in debug, crashes in release, "works on my machine."

## Code in this folder
- `main.cpp` — compiles and runs (no syntax error) but the sum-of-1-to-10 loop has a classic semantic error: `i <= 10` vs. `i < 10`, plus the accumulator is uninitialized. Read it, predict the output, then run it.

## Gotchas
- A single syntax error often cascades into dozens of follow-up errors. Fix the *first* one reported, then recompile — don't try to read all of them.
- "It compiles" is not "it works." Semantic correctness needs tests, not the compiler.

## Run
    make 3.01
