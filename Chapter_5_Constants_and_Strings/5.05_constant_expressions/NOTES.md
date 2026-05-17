# 5.5 — Constant expressions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/constant-expressions/

## Why it matters
Some places in C++ *require* a value the compiler knows at compile time: array sizes, template arguments, `case` labels, non-type template parameters, `static_assert` conditions. Those places only accept **constant expressions**. Knowing what is and isn't a constant expression is the prerequisite for understanding `constexpr` (5.6) and `consteval`.

## Key points
- A **constant expression** is one the compiler can fully evaluate at compile time.
- Inputs allowed in a constant expression:
  - Literals (`42`, `3.14`, `"hi"`).
  - `const` integral variables initialized from a constant expression.
  - `constexpr` variables (5.6).
  - `constexpr`/`consteval` function calls.
- Inputs *not* allowed: ordinary variables, function parameters (in a non-`constexpr` function), values read from `std::cin`, return values of non-`constexpr` functions.
- `const int n{ getInput() };` is *not* a constant expression — `n` is `const` but its value is only known at runtime. You cannot use it as an array size.
- `const int n{ 10 };` *is* a constant expression — initialized from a literal, integral type, value visible to the compiler.
- For non-integral types, plain `const` doesn't promote to constant-expression status. Use `constexpr`.

## Code in this folder
- `main.cpp` — three `const` declarations, two of which are constant expressions and one of which isn't, with `static_assert` proving which is which.

## Gotchas
- "Compile-time known" is stricter than "fixed for the program's lifetime." Reading from `argv` once and storing it in a `const` doesn't make it a constant expression.
- `const double pi{ 3.14 };` is *not* a constant expression in C++ pre-C++26 (only integral `const`s are). Use `constexpr double pi{ 3.14 };` instead.
- A `constexpr` function *may* be called at runtime too; the compiler picks compile-time only if all arguments are themselves constant expressions and the result is used in a constant-expression context.

## Run
    make 5.05
