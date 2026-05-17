# 8.9 — Do-while statements

> learncpp.com: https://www.learncpp.com/cpp-tutorial/do-while-statements/

## Why it matters
`do-while` is the only loop form that **always runs at least once**. The condition is checked **after** the body, not before. There's exactly one common use case: "prompt the user, validate their input, re-prompt if it was invalid." You always need to prompt at least once; the condition is "input was bad."

For anything else, prefer `while` or `for` — the condition-at-the-top form is easier to read because the entry condition is visible before the body.

## Key points
- Shape: `do { ... } while (cond);` — note the **trailing semicolon** after `while(cond)`. Forgetting it is a parse error a beginner sees once and never again.
- Evaluation order: **run body → check condition → maybe loop again.** Always at least one execution.
- The variables used in the condition must be in scope where `while (cond)` is — i.e., outside the `do { ... }` block, since the block ends before the condition. This is a small but real footgun: you can't declare the loop variable inside the body.
- Canonical use: input validation. `do { prompt; read x; } while (x is invalid);`
- If a `while` form fits naturally, prefer it. `do-while` "runs at least once even when you didn't mean it to" is a surprisingly common bug source.

## Code in this folder
- `main.cpp` — input validation (re-prompts on bad input), plus a deliberate menu-prompt loop. No interactive `cin` in the demo — we simulate input from a small array so the build is reproducible.

## Gotchas
- The condition is evaluated **at the bottom**, but the variable scope still ends at `}`. Declare the variable before the `do`, not inside the body, if you want to test it in the condition.
- Don't use `do-while` "just to save a check." If reordering as a `while` is awkward, fine. If it's just as clear, use `while`.

## Run
    make 8.09
