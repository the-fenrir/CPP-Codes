# 6.6 — The conditional operator

> learncpp.com: https://www.learncpp.com/cpp-tutorial/the-conditional-operator/

## Why it matters
The ternary is the only place in C++ you can write a *conditional expression* — an `if` that produces a value. That single property makes it irreplaceable when initializing a `const`, returning a value, or building a stream-insertion. Everywhere else, an `if` statement is usually clearer; pick deliberately.

## Key points
- Syntax: `cond ? when_true : when_false`. Only one of the two arms is evaluated.
- It's the only **ternary** operator in C++ — three operands.
- Both arms must have a common type (or be convertible to one). `b ? 1 : "no"` won't compile.
- Useful spots:
    - **Initializing a `const` whose value depends on a condition**: `const int x = (cond ? 1 : 2);` — you cannot do this with an `if`-statement.
    - **Inside stream insertion**: `std::cout << (n == 1 ? "apple" : "apples");`.
    - **Returning** from a function: `return (a > b ? a : b);`.
- **Parenthesize**:
    - the whole `?:` expression when it's part of a larger expression (it has near-the-bottom precedence — lower than `<<`, comparison, arithmetic);
    - the condition itself if it contains operators (visual clarity, not strictly required).

## Code in this folder
- `main.cpp` — the canonical `max`-of-two, `const`-init use, stream-insertion pluralization, and a deliberately bad nested ternary to show *when not to*.

## Gotchas
- Nested ternaries (`a ? b : (c ? d : e)`) read terribly. After one level of nesting, switch to `if`/`else if`.
- `std::cout << a ? b : c;` parses as `(std::cout << a) ? b : c;` — almost certainly not what you meant. Parenthesize.
- Type-mismatch errors here are confusing because the compiler tries hard to find a common type — read the diagnostic carefully if the arms differ in const-ness or signedness.

## Run
    make 6.06
