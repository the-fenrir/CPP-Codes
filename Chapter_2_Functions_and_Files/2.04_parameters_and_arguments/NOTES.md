# 2.4 — Introduction to function parameters and arguments

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-function-parameters-and-arguments/

## Why it matters
Returning a value is half the story. Parameters are the other half: they let a function take input from the caller, so the same code can do different work each call. Pass-by-value's "the function gets its own copy" semantics is the single most important rule to internalize in this chapter.

## Key points
- A **parameter** is a variable declared in the function definition; an **argument** is the value the caller supplies.
- Default in C++ is **pass by value**: the parameter is initialized as a copy of the argument. Modifying the parameter inside the function does *not* affect the caller's value.
- Parameter list is comma-separated: `int add(int a, int b)`.
- An empty parameter list is `()` (or the more explicit `(void)` in C-style, rarely used in C++).
- Arguments are evaluated before the call; their order of evaluation between commas is unspecified — don't rely on side effects.

## Code in this folder
- `main.cpp` — `add()` takes two parameters; `tryToZero()` demonstrates that pass-by-value can't mutate the caller's variable.

## Gotchas
- Mismatched argument count or types is a compile error.
- `f(x++, x++)` has unspecified evaluation order — undefined which `x` each parameter sees.
- "Pass by value copies" includes large structures: that's why later chapters introduce pass-by-reference.

## Run
    make 2.04
