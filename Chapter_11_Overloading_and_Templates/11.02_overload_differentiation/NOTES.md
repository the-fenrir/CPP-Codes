# 11.2 — Function overload differentiation

> learncpp.com: https://www.learncpp.com/cpp-tutorial/function-overload-differentiation/

## Why it matters
For overloading to work, the compiler must be able to tell the overloads apart purely from the *declaration*. The rules are surprisingly narrow: differing **number** of parameters, or differing **parameter types** (excluding aliases and top-level `const`). Return type is **not** part of the signature for this purpose. Knowing exactly what counts saves you from "but they look different to me" compile errors.

## Key points
- Overloads can differ by:
  - **Number** of parameters.
  - **Type** of parameters (after typedef/alias resolution).
  - For member functions: `const` / `volatile` / **ref-qualifiers** on the *implicit object parameter*.
- Overloads **cannot** differ by:
  - **Return type alone.**
  - **Top-level `const`** on a by-value parameter — `void f(int)` and `void f(const int)` are the same overload (the parameter is a local copy either way).
  - Typedef aliases — `using Age = int;` then `f(int)` vs `f(Age)` is one function.
- **Type template parameters** (11.6) participate in overload sets too; templates and non-templates can coexist with priority rules (11.7).

## Code in this folder
- `main.cpp` — what differentiates and what doesn't. Lines that would not compile are commented out with the reason.

## Gotchas
- `void f(int)` vs `void f(int&)` are different overloads (different *parameter types*). Easy to confuse with the top-level `const` rule above.
- `void f(int*)` vs `void f(const int*)` are different (low-level `const` is part of the type).
- Default arguments don't differentiate — `void f(int)` and `void f(int, int = 0)` are ambiguous when called with one arg.

## Run
    make 11.02
