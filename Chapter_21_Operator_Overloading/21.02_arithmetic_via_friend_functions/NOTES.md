# 21.2 — Overloading arithmetic operators using friend functions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/overloading-the-arithmetic-operators-using-friend-functions/

## Why it matters
For a binary arithmetic operator like `+` or `-`, the implementation usually needs to peek at *private* members of both operands. A `friend` declaration grants that access without turning the operator into a member function — keeping it **symmetric** (both operands are normal parameters) so that `5 + c` and `c + 5` can both be written with mixed types.

## Key points
- `friend Cents operator+(const Cents& a, const Cents& b);` declared inside the class.
- The function is **not** a member; it's a free function with private access. So you must define it outside (or inline-define inside the class body).
- Symmetry matters: you can write **three** overloads to cover `Cents + Cents`, `Cents + int`, `int + Cents`. Member-function overloads can't do the last one (the left operand `int` has no `operator+` member).
- A common shortcut: write `operator+(Cents, int)` and `operator+(int, Cents)` by delegating to the symmetric `Cents + Cents` after converting the `int`.
- `friend` is *not* a class membership boost — it's surgical access. Use it only when needed.

## Code in this folder
- `main.cpp` — `Cents` with three friend-`operator+` overloads. Demonstrates the mixed-int case that members can't handle.

## Gotchas
- Prefer **non-friend** if the public interface suffices (the 21.01 version did). Adding `friend` widens the class's trust boundary; pay that cost only when needed.
- Defining the friend inside the class body works but means you can't separate declaration and definition cleanly across a header/source split.

## Run
    make 21.02
