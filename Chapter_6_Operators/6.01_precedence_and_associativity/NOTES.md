# 6.1 — Operator precedence and associativity

> learncpp.com: https://www.learncpp.com/cpp-tutorial/operator-precedence-and-associativity/

## Why it matters
Every expression is a small parse tree. Two rules build that tree: **precedence** (which operator binds tighter) and **associativity** (left-to-right or right-to-left when ties). Get those wrong and the code does something quietly different from what you meant — and reviewers won't catch it because it *looks* correct.

A third concept lurks underneath: **order of evaluation** of operands is *not* fixed by precedence. `f() + g()` may call `g()` first. This is the seed of the side-effect bugs in 6.4.

## Key points
- **Operand** = input value, **operator** = the symbol, **operation** = the whole thing.
- **Arity**: unary (one operand: `-x`), binary (two: `x + y`), ternary (three: `c ? x : y`). Most operators are binary.
- **Precedence**: assigned a level; lower number = binds tighter. `*` (5) before `+` (6) → `4 + 2 * 3` ≡ `4 + (2 * 3)`.
- **Associativity** breaks ties at the same precedence. Subtraction is left-to-right: `7 - 4 - 1` ≡ `(7 - 4) - 1`. Assignment is right-to-left: `a = b = c` ≡ `a = (b = c)`.
- **Parentheses override everything.** Use them whenever the answer wouldn't be instantly obvious to a reader.
- **Value computation ≠ operand evaluation.** Precedence governs which operator computes its value first; it says nothing about *when each operand is evaluated*. Operands may be evaluated in any order (since C++17 some operators got tightened, but in general: don't rely on it).

## Code in this folder
- `main.cpp` — three expressions where precedence/associativity changes the answer, plus a demo of unspecified operand evaluation order.

## Gotchas
- "I'll just memorize the precedence table." Don't. Parenthesize anything non-trivial. The compiler doesn't care; the next person reading the code does.
- `<<` (stream insertion) has *much* lower precedence than `+`, but *higher* than `?:`. `std::cout << (a ? "y" : "n");` needs the parens.
- Don't confuse "left-associative" with "left operand evaluated first." Those are unrelated.

## Run
    make 6.01
