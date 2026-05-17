# 10.8 — Type deduction for objects using the `auto` keyword

> learncpp.com: https://www.learncpp.com/cpp-tutorial/type-deduction-for-objects-using-the-auto-keyword/

## Why it matters
When the initializer already tells you the type, repeating it adds noise and a place for the two halves to drift apart (`int x = some_function_returning_long();` — silent narrowing). `auto` lets the compiler deduce the variable's type from its initializer. Used judiciously, it removes redundancy without removing clarity.

## Key points
- `auto x = expr;` declares `x` with the type of `expr`, after dropping top-level `const` and references.
- **Requires an initializer.** `auto x;` is ill-formed — there's nothing to deduce from.
- Deduction strips `&` and top-level `const` by default. Add them back explicitly when you want them:
  - `auto       x = obj;`   // copy
  - `const auto x = obj;`   // const copy
  - `auto&      x = obj;`   // non-const reference (binds to non-const lvalue)
  - `const auto& x = obj;`  // read-only reference, avoids the copy
- Literal suffixes matter: `auto x = 5;` is `int`; `auto x = 5u;` is `unsigned`; `auto x = 5.0;` is `double`; `auto x = 5.0f;` is `float`.
- With list init: `auto x{ 5 };` is `int` (C++17 rule for single-element brace). `auto x = { 5 };` is `std::initializer_list<int>`. Use `=`-init or paren-init for scalars to avoid surprise.

## Code in this folder
- `main.cpp` — basic deductions, copy vs. ref vs. const-ref, and the literal-suffix gotcha.

## Gotchas
- `auto` doesn't change conversion rules — it just inherits them. `auto avg = a / b;` where both are `int` is still integer division.
- Loop variable footgun: `for (auto x : container)` *copies*. For non-trivial element types use `for (const auto& x : container)`, or `for (auto& x : container)` when you intend to mutate.
- Reading reviews suffers when types are non-obvious. Don't `auto` a call whose return type the reader needs to know — write it out.

## Run
    make 10.08
