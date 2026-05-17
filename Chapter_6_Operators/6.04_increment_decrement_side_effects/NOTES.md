# 6.4 — Increment/decrement, and side effects

> learncpp.com: https://www.learncpp.com/cpp-tutorial/increment-decrement-operators-and-side-effects/

## Why it matters
`++` and `--` look like cute shortcuts but they're the most common source of *undefined behavior* in everyday C++. The reason: they mutate a variable **and** produce a value, and the language deliberately leaves the order of those side effects underspecified across most operators. So `i = i++ + ++i;` doesn't have a "right answer" — different compilers can legally give different results.

## Key points
- **Prefix** `++x` / `--x`: increment first, then yield the **new** value. Returns an lvalue.
- **Postfix** `x++` / `x--`: yield the **old** value, then increment. Returns a prvalue (a copy).
- Prefer prefix when both work — postfix has to make a copy of the old value.
- A **side effect** is any observable change beyond the result of the expression: writing a variable, doing I/O, etc.
- **The rule**: don't use a variable that has a side effect applied to it more than once in the same statement. Doing so is undefined behavior in pre-C++17 and still hazardous afterward.
- `foo(i, i++)` is also UB: function-argument evaluation order is unspecified.

## Code in this folder
- `main.cpp` — prefix vs. postfix demo, then an `i++` in a couple of separate statements (the *safe* way) — pointedly avoiding the UB construct.

## Gotchas
- "But my compiler gives me X!" UB means *any* answer is allowed. Today's lucky output is tomorrow's bug after an optimizer upgrade.
- Mixing `++` with stream insertion is also dangerous: `std::cout << i++ << i;` — order of evaluation of `<<` operands was UB before C++17 and is still confusing.
- `for (int i = 0; i < n; ++i)` is safer and slightly faster than `i++` (for primitives the compiler usually erases the difference; for class iterators it can be real).

## Run
    make 6.04
