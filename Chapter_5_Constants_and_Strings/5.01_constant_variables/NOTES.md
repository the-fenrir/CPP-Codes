# 5.1 — Constant variables (named constants)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/constant-variables-named-constants/

## Why it matters
A variable is "the value can change." A *named constant* is "this value is fixed and the compiler will enforce it." That enforcement is the whole point: it documents intent, catches accidental writes, and lets the optimizer see opportunities it can't see through a plain variable. It's also the entry point to every other "constness" topic in this chapter.

## Key points
- Declare with `const T name { value };`. Must be initialized at the point of declaration — there's no second chance.
- `const` binds to whatever's on its left, or to the thing on its right if it's leftmost. `const int` and `int const` are the same type. Stick to one (this repo uses `const int`).
- A `const` variable's value is fixed for that object's lifetime, but it isn't necessarily known at compile time — `const int x{ getInput() };` is legal. Compile-time constness is `constexpr` (5.6).
- Prefer named constants over magic numbers. `const double gravity{ 9.8 };` reads better than a bare `9.8` sprinkled through the code, and changes happen in one place.
- Function parameters can be `const` too (`void f(const int n)`), which is a promise *to yourself* that you won't reassign the parameter inside the function. Rarely necessary for value parameters; very common for reference parameters.

## Code in this folder
- `main.cpp` — declaring a `const`, attempting to reassign it (shown commented), runtime-initialized `const`, and a `const` parameter.

## Gotchas
- `const` without an initializer is a compile error. The compiler can't help you "forget to set it later."
- Don't confuse "the variable is const" with "the value is known at compile time." Only the second one lets you use it as an array size, template argument, etc. (5.5–5.6).
- Macros (`#define PI 3.14`) are *not* constants — they're text substitution with no type, no scope, and no debugger visibility. Use `const`/`constexpr` instead.

## Run
    make 5.01
