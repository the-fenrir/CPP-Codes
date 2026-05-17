# 12.2 — Value categories (lvalues and rvalues)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/value-categories-lvalues-and-rvalues/

## Why it matters
Every expression has two properties: its **type** (e.g. `int`) and its **value category** (lvalue or rvalue). Value categories explain why `5 = x;` is an error, why `int& r = 5;` is an error, and why `const int& r = 5;` works. The rest of the chapter — and every later discussion of move semantics, perfect forwarding, returning references — is built on this distinction.

## Key points
- **lvalue**: an expression that identifies a function or an object with an identity (it has a name/address that persists). Lvalues can appear on the left of `=`. Example: `x`, `arr[0]`, `*ptr`.
- **rvalue**: an expression that is *not* an lvalue. Typically literals, temporaries, and the result of most operators. Example: `5`, `x + 1`, `foo()` (when `foo` returns by value).
- Historical mnemonic ("l-value can appear on the **L**eft of `=`") is incomplete: `const int x;` is an lvalue but can't be assigned to. Better mental model: lvalues have **identity** (you can take their address), rvalues are **transient**.
- An lvalue **implicitly converts** to an rvalue when needed (e.g. `int y = x;` — `x` is an lvalue, but the right-hand side wants an rvalue, so it converts).
- A **modifiable lvalue** is an lvalue that isn't `const`. Only modifiable lvalues can appear on the left of `=`.
- C++11 added further subcategories (xvalue, prvalue, glvalue) for move semantics — chapter 12 stays at the lvalue/rvalue level.

## Code in this folder
- `main.cpp` — concrete examples of each, plus a deliberately commented-out illegal case.

## Gotchas
- "lvalue" is a property of **expressions**, not of objects or types. `x` is an lvalue expression. `int` is a type, not an lvalue.
- A function call is an lvalue if the function returns by reference; it's an rvalue if the function returns by value. This matters for chaining and for whether you can take the address of the call.
- Literals are *almost* always rvalues. Exception: string literals (`"hello"`) are lvalues — they live in static storage and have an address.

## Run
    make 12.02
