# 8.7 — Goto statements

> learncpp.com: https://www.learncpp.com/cpp-tutorial/goto-statements/

## Why it matters
`goto` exists in C++ and you should know it does, both so you can read it in legacy code and so you can recognize when not to write it. Almost every legitimate use of `goto` has a structured replacement: `break`/`continue` for loops, `return` for early exits, RAII destructors for cleanup. The one remaining niche — breaking out of *deeply nested* loops — is rare enough that you should pause and ask whether the function should just be refactored.

## Key points
- Shape: a **label** is `name:` followed by a statement, anywhere in a function; `goto name;` jumps to it.
- Scope is *function-local*. You can `goto` forward or backward, but not into a different function and not into a block whose variables would skip initialization.
- A `goto` that **skips over a variable initialization** is a compile error for non-trivial types and undefined behavior for trivial ones. The language is protecting you from "use of uninitialized variable" the only way it can.
- Practically every justification for `goto` in C ("cleanup before return", "break out of nested loops") has a better C++ tool: destructors (RAII) for cleanup, a flag + nested `break`, or extracting the inner loop into a function with `return`.
- One semi-defensible use: jumping forward to a single shared cleanup label in C-style code that can't use destructors. Rare in modern C++.

## Code in this folder
- `main.cpp` — a labeled forward `goto` used to break out of a nested loop, then the same logic rewritten with extracted-function + `return`. Compare them.

## Gotchas
- The compiler error on "jump bypasses variable initialization" is *not* a warning — it's a hard error for non-trivially-constructed types. Move the declaration before the label or add a block.
- A `goto` that jumps *backward* creates a loop with no compiler-checkable termination. If you're tempted to do this, you wanted a `while`.

## Run
    make 8.07
