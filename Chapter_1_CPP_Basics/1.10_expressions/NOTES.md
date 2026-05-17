# 1.10 — Introduction to expressions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-expressions/

## Why it matters
Most of the code you'll ever write is **expressions**. An expression is anything that produces a value when evaluated. Once you see code as a tree of expressions inside statements, larger language features (function calls, control flow, operators) become composition rather than memorization.

## Key points
- An **expression** is a combination of literals, variables, operators, and function calls that evaluates to a single value.
- An **expression statement** is an expression followed by a `;` — that's how an expression becomes a side effect.
  - `x = 5;` is an assignment expression turned into a statement.
  - `std::cout << "hi";` is an expression statement.
- **Sub-expressions** compose: `(a + b) * c` has two sub-expressions, `a + b` and `(...) * c`.
- Expressions have a **type** and a **value**. `5 + 3` has type `int` and value `8`.
- An expression with no side effect and a discarded value is dead code: `x + 1;` compiles but does nothing useful.

## Code in this folder
- `main.cpp` — a few expressions, their values, and a nested one.

## Gotchas
- `x++` is an expression with both a value (the old `x`) and a side effect (incrementing `x`). Don't write `a = x++ + ++x;` — order of side effects within a single expression can be unspecified.
- An expression statement that has no observable effect (e.g. `x + 1;`) is usually a typo for `x += 1;`.

## Run
    make 1.10
