# 21.5 — Overloading operators using member functions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/overloading-operators-using-member-functions/

## Why it matters
Some operators *must* be members: `=`, `[]`, `()`, `->`. Some operators *should* be members when the left operand is your class and the operator naturally mutates or returns *this*: compound assignments (`+=`, `-=`, `*=`), pre/post increment, etc. Member overloads have implicit access to `this`, which is exactly what you want when the operator is "do something *to* the object on the left."

## Key points
- Member overload signature: the left operand is implicit (`this`); only the right operand is a parameter.
  - `Cents Cents::operator+(int n) const { ... }`
- Member overloads **can't** swap operands. `5 + cents` won't resolve to a `Cents` member; only `cents + 5` does. (Hence friend/free for the int-on-left case in 21.02.)
- Decision matrix:
  - `=`, `[]`, `()`, `->` → must be member.
  - `<<`, `>>` → must be non-member (left operand is `std::ostream`/`std::istream`).
  - Compound assignment (`+=` etc.), unary ops modifying state → member.
  - Symmetric binary (`+`, `-`, `==`, `<`) → non-member is the safer default.
- Common idiom: implement `operator+=` as a member, then implement non-member `operator+` in terms of it.

## Code in this folder
- `main.cpp` — `Cents` with member `operator+= ` and non-member `operator+` that delegates to it (the canonical pattern).

## Gotchas
- Returning `*this` by reference is correct for compound assignment (`+=` returns `Cents&`); returning by value is correct for `+` (it must produce a fresh object).
- A `const` member overload (`Cents operator+(int) const`) is the right default for non-mutating binary ops — it lets you write `const Cents c; c + 1;`.

## Run
    make 21.05
