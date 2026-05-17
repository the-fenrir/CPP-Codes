# 2.2 — Function return values

> learncpp.com: https://www.learncpp.com/cpp-tutorial/function-return-values-value-returning-functions/

## Why it matters
A function that prints to the screen is useful but coupled to I/O. A function that *returns a value* is composable — its output can flow into another expression, another function, or be stored. This is what turns functions into building blocks.

## Key points
- A value-returning function declares its **return type** before its name: `int getAnswer()`.
- The `return` statement supplies that value back to the caller and ends the function.
- `main()` returns an `int`: `0` = success, non-zero = some kind of failure. `main` is special — falling off the end implicitly returns `0`.
- **Don't Repeat Yourself (DRY)**: if a value is computed once but needed in several places, return it.
- A function that promises to return a value must always do so on every path — otherwise undefined behavior.

## Code in this folder
- `main.cpp` — `getRandomNumber()` returns an int, and the caller uses the return value in an expression.

## Gotchas
- Forgetting `return` in a non-void function compiles (with a warning) but produces undefined behavior at runtime.
- Calling a value-returning function and ignoring its return value is legal but usually a sign of a design problem.
- `return;` (no value) is a compile error in a non-void function.

## Run
    make 2.02
