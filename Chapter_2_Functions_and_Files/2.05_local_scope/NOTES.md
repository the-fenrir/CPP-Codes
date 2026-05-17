# 2.5 — Introduction to local scope

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-local-scope/

## Why it matters
A variable declared inside a function is invisible outside it, and dies when the function returns. This single rule prevents an enormous class of bugs — distant code can't accidentally read or write your locals. Understanding scope (compile-time visibility) vs. lifetime (runtime existence) is also what lets you reason about why returning a pointer to a local is wrong later.

## Key points
- A **local variable** is defined inside a function (or block). Its **scope** ends at the closing `}` of that block.
- **Lifetime**: locals are created when their definition is reached and destroyed when their enclosing block ends.
- **Scope is compile-time**, **lifetime is runtime**. They overlap for locals but the distinction matters elsewhere (e.g. dangling references).
- Parameters are locals of the function body — same scope, same lifetime.
- Each call creates a fresh set of locals; values don't persist between calls.

## Code in this folder
- `main.cpp` — two functions each have a local `count`; they don't interfere.

## Gotchas
- Two unrelated functions can name a variable the same thing — they're different variables.
- A "static local" (later chapter) survives calls; a plain local does not. Don't assume persistence.
- Returning a pointer or reference to a local is undefined behavior. The local is gone.

## Run
    make 2.05
