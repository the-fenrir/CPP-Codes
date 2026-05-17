# 6.5 — The comma operator

> learncpp.com: https://www.learncpp.com/cpp-tutorial/the-comma-operator/

## Why it matters
There's a comma *operator* (one expression) and a comma *separator* (function args, declarations, initializer lists). They look identical and behave nothing alike. The operator evaluates both sides and returns the right — quietly enough that `z = a, b;` does not do what most people read.

## Key points
- **Comma operator `e1, e2`**: evaluate `e1`, discard its result, evaluate `e2`, yield `e2`'s value. Sequenced left-to-right (rare guarantee in C++).
- **Lowest precedence in the language** — lower than assignment. `z = a, b;` parses as `(z = a), b;` → `z` becomes `a`, `b` is computed and discarded.
- To actually assign the comma-result, wrap it: `z = (a, b);` → `z` is `b`.
- **Comma separator** is *not* the same operator: parameter lists, argument lists, variable declarations, and `{}`-initializer lists use commas as syntax, not as the comma operator.
- Idiomatic spot: a `for` header — `for (int i = 0, j = n; i < j; ++i, --j)`. Outside that, prefer two statements.

## Code in this folder
- `main.cpp` — the precedence trap (`z = a, b;`), the explicit-parens fix, and the for-loop idiom.

## Gotchas
- `int a, b = 5;` — that comma is a separator. It declares `a` (uninitialized!) and `b` (=5). Easy to misread.
- Avoid `cout << (++i, ++j);` style "tricks". You're substituting cleverness for clarity.
- `std::cin >> x, y;` looks like it reads two values; it actually reads one and evaluates `y` for nothing.

## Run
    make 6.05
