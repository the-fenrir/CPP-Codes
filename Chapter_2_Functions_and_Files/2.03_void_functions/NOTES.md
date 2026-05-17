# 2.3 — Void functions (non-value-returning functions)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/void-functions-non-value-returning-functions/

## Why it matters
Not every function produces a value. Some exist purely for their side effect — printing, mutating state, logging. `void` is the explicit "this function returns nothing" marker, and using it correctly keeps the type system honest.

## Key points
- Declare with return type `void`: `void log(const std::string& m)`.
- A void function may use `return;` (no value) to exit early, but doesn't have to.
- You can't use a void function call where a value is expected: `int x{ log("hi") };` is a compile error.
- Returning a value from a void function is a compile error.
- Falling off the end of a void function is fine — there's nothing to return.

## Code in this folder
- `main.cpp` — `printGreeting()` returns nothing; `printAbs()` uses an early `return;` to short-circuit.

## Gotchas
- `void f() { return 5; }` doesn't compile.
- `void f();` followed by `int x{ f() };` doesn't compile either — but if you mistakenly typed `int f();` the call would compile and read garbage.

## Run
    make 2.03
