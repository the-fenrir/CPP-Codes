# 6.8 — Logical operators

> learncpp.com: https://www.learncpp.com/cpp-tutorial/logical-operators/

## Why it matters
`!`, `&&`, `||` compose conditions. They look obvious, but two real subtleties bite: **short-circuit evaluation** (the right operand may never run, which matters if it has side effects) and **precedence** (`!`, `&&`, `||` are in decreasing strength — the usual mistake is forgetting that `!x > y` is `(!x) > y`).

## Key points
- **`!x`** — true iff `x` is false. Highest precedence of the three (and very high overall).
- **`a && b`** — true iff both are true. Short-circuits: if `a` is false, `b` is **not evaluated**.
- **`a || b`** — true iff either is true. Short-circuits: if `a` is true, `b` is **not evaluated**.
- Precedence order: `!` > arithmetic > comparison > `&&` > `||`. So `a < b && c < d` parses as `(a < b) && (c < d)` — no parens needed for that one.
- Mixed `&&`/`||`: `a && b || c && d` is `(a && b) || (c && d)`. **Parenthesize anyway** — readers shouldn't have to remember the precedence to follow a condition.
- **No logical XOR.** For two `bool`s, `a != b` does it (true iff they differ).
- **De Morgan's laws**: `!(a && b) == (!a || !b)`, `!(a || b) == (!a && !b)`. Useful when inverting a condition for an early return.

## Code in this folder
- `main.cpp` — short-circuit guarding a null/divide-by-zero, the `!x > y` trap, De Morgan, and XOR via `!=`.

## Gotchas
- `if (!x > y)` — common mistake; means `if ((!x) > y)`, not `if (!(x > y))`.
- Side-effecting right-hand operands behind `&&`/`||` may never run: `if (ptr && consume(ptr))` — fine; `if (consume(ptr) && ptr)` — could crash if `ptr` is null but `consume` runs first.
- Bitwise `&` and `|` are **not** logical operators. They don't short-circuit and they operate bit-by-bit. Don't substitute one for the other.

## Run
    make 6.08
