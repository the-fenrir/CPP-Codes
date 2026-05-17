# 8.3 — Common if statement problems

> learncpp.com: https://www.learncpp.com/cpp-tutorial/common-if-statement-problems/

## Why it matters
`if` looks deceptively simple. The bugs are all about *exactly which body each `if`/`else` binds to* and *what your condition actually evaluates*. Once you've internalized these patterns you'll spot them in code review without thinking.

## Key points
- **Nested `if` and the dangling `else`.** An `else` binds to the **nearest unmatched `if`** in the same scope, not to whichever one your indentation suggests. Braces remove all ambiguity:
  ```cpp
  if (a)
      if (b) doX();
      else   doY();   // binds to inner `if (b)`, NOT outer `if (a)`
  ```
- **Null statements.** A stray semicolon after `if (cond);` makes the body empty. Easy to introduce when refactoring. `-Wempty-body` flags it.
- **Assignment in condition.** `if (x = 5)` assigns 5 to x and treats the result as true. Some style guides write `if (5 == x)` so a missing `=` won't compile. Modern compilers warn with `-Wparentheses`.
- **Operator precedence in conditions.** `if (a == b & c == d)` does bitwise-AND of two bools — works by accident but means the wrong thing. Use `&&`. Parenthesize when in doubt: `if ((a == b) && (c == d))`.
- **Comparing floats with `==`.** Almost always wrong — see ch.6. Use a tolerance.
- **Operator chaining doesn't do what math does.** `if (0 < x < 10)` parses as `(0 < x) < 10` — a bool compared to 10 — always true. Write `if (0 < x && x < 10)`.

## Code in this folder
- `main.cpp` — each pitfall demoed and then shown corrected.

## Gotchas
- Compiler warnings are doing real work here. Build with `-Wall -Wextra -Wpedantic` and *act* on the warnings — most of this lesson is a list of things the compiler will warn you about if you let it.
- A non-bool condition is implicitly converted (`if (ptr)`, `if (n)`). Fine in isolation; nasty when combined with operator chaining or assignment.

## Run
    make 8.03
