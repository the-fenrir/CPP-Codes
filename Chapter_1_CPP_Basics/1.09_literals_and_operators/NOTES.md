# 1.9 — Introduction to literals and operators

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-literals-and-operators/

## Why it matters
A program does work by combining **values** using **operators**. Literals are the values you write directly in code; operators are the verbs. Recognising the two by sight is step one toward reading any expression fluently.

## Key points
- **Literal** = a value baked into the source code. `5`, `3.14`, `'A'`, `"hello"`, `true`.
- **Operator** = a symbol that performs an operation on one or more operands.
  - **Unary** — one operand: `-x`, `!flag`.
  - **Binary** — two operands: `a + b`, `x < y`, `a = b`.
  - **Ternary** — three operands: `cond ? a : b` (the only one in C++).
- Operators have **precedence** (which binds tighter, like multiplication over addition) and **associativity** (left-to-right or right-to-left). Brackets win over both — use them when in doubt.
- `=` (assignment) is an operator too, and it returns the assigned value. That's why `a = b = 0;` works.

## Code in this folder
- `main.cpp` — examples of literals and unary / binary / ternary operators.

## Gotchas
- `=` is assignment, `==` is comparison. `if (x = 5)` compiles, assigns 5 to `x`, and is almost certainly a bug.
- Integer literal `5` and floating literal `5.0` are different types — mixing them can trigger conversions you didn't intend.

## Run
    make 1.09
