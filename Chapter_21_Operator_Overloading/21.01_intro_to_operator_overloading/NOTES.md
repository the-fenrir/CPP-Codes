# 21.1 — Introduction to operator overloading

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-operator-overloading/

## Why it matters
Operator overloading is **function overloading with funny names**. `a + b` is sugar for `operator+(a, b)` (or `a.operator+(b)`). Giving your class an `operator+` lets calling code stay readable — `total = price + tax;` instead of `total = add(price, tax);`. The catch: the syntax invites *unintuitive* meanings. Overloading `+` for "concatenate two log files" reads fine; overloading `+` to do "send email" is sabotage. Operators carry built-in expectations and you inherit them.

## Key points
- Almost every operator can be overloaded. The exceptions are: `?:`, `::`, `sizeof`, `.`, `.*`, `typeid`.
- You can't invent new operators (`**`), can't change arity (no unary `/`), can't change precedence/associativity, and can't overload operators between **two** built-in types — at least one operand must be a class/enum type.
- An overload is just a function — same overload resolution, same return-type freedom (within reason).
- Three forms exist: **member function**, **friend function**, **normal (non-friend, non-member) function**. Picking between them is what the next four lessons are about.
- Default rule of taste: keep the operator's semantics roughly what programmers expect. `+` should be commutative-ish and non-mutating. If it isn't, name a real function instead.

## Code in this folder
- `main.cpp` — a `Cents` class with a free-function `operator+`, showing the rewrite from `add(c1, c2)` to `c1 + c2`.

## Gotchas
- "Can I overload `&&` and `||`?" Yes, but you lose **short-circuit evaluation** — overloaded versions are function calls, so both operands are always evaluated. Almost always wrong.
- Don't overload `operator,` (comma). Same short-circuit-style trap, plus it's an evaluation-order foot-cannon.
- Overloads can't have default arguments (with one exception in 21.08 for post-increment).

## Run
    make 21.01
