# 6.2 — Arithmetic operators

> learncpp.com: https://www.learncpp.com/cpp-tutorial/arithmetic-operators/

## Why it matters
The arithmetic operators look trivial — but `/` quietly changes meaning based on operand types, and `/` by zero changes meaning again based on whether the operands are integer or floating point. Most "off by one in division" bugs are actually integer-division bugs.

## Key points
- **Unary**: `+x` (returns x), `-x` (negates). Unary `+` exists mostly for symmetry; it's rarely useful.
- **Binary**: `+ - * / %` — addition, subtraction, multiplication, division, remainder.
- **Integer division** (both operands integer): result is truncated toward zero. `7 / 4` → `1`, `-7 / 4` → `-1`.
- **Floating-point division** (at least one operand floating): full fractional result. `7.0 / 4` → `1.75`. Cast with `static_cast<double>(...)` to force float division.
- **Division by zero**: integer → undefined behavior; floating point → typically `inf` or `nan` (IEEE 754, implementation-defined).
- **Compound assignment**: `+=`, `-=`, `*=`, `/=`, `%=` — shorthand for `x = x ⊕ expr`. Evaluates the left-hand side once.

## Code in this folder
- `main.cpp` — integer vs. float division, the cast trick, and float division by zero.

## Gotchas
- `avg = (a + b) / 2;` with int operands truncates. If you wanted a float average, cast: `(a + b) / 2.0`.
- `int x = -7 / 4;` is `-1`, not `-2`. C++ truncates toward zero, not toward negative infinity.
- `0.0 / 0.0` is `nan`, and `nan == nan` is **false** (see 6.7).

## Run
    make 6.02
