# 21.6 — Overloading unary `+`, `-`, and `!`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/overloading-unary-operators/

## Why it matters
Unary operators take one operand — the object they're applied to. The natural form is a `const` **member function** with no parameters: `T T::operator-() const`. Use them sparingly; the meaning of unary `-` on a `Point` is obvious, but unary `!` on a domain class is often clearer as a named member like `isEmpty()`.

## Key points
- Member form: zero parameters, returns a new value, marked `const`.
  - `Cents operator-() const { return Cents{ -m_cents }; }`
- Unary `+` rarely does anything useful; usually a no-op identity. Provide only if it makes idiomatic sense (e.g. promotes via integer rules).
- Unary `!` should return `bool` and answer "is this object in a 'false-y' / empty state?" Implies you also have a notion of empty.
- Friend/non-member form is legal but adds no value here — there's no "swap operand" symmetry for a unary op.

## Code in this folder
- `main.cpp` — `Cents` with unary `-`; `Point` with unary `-` (negate each coordinate) and `!` (is-origin test).

## Gotchas
- Unary `-` returning a *new* value is correct; don't mutate `*this`. `auto b = -a;` shouldn't change `a`.
- Don't conflate unary `-` (negation) with binary `-` (subtraction); they're separate overloads even though both are called `operator-`. The compiler disambiguates by parameter count.
- If you overload `!`, also think about `operator bool()` (lesson 21.11). They overlap.

## Run
    make 21.06
