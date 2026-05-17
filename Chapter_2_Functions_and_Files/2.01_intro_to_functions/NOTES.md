# 2.1 — Introduction to functions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-functions/

## Why it matters
A program that lives entirely inside `main()` quickly stops fitting in your head. Functions let you name a chunk of work, call it from anywhere, and reason about it in isolation. Every later abstraction in C++ — classes, templates, lambdas — is ultimately "a function with extra rules."

## Key points
- A **function** is a reusable sequence of statements with a name.
- Calling syntax: `identifier()`. The parentheses are how the compiler tells "call this thing" from "name this thing."
- Execution is non-linear: hitting a call jumps to the function, runs its body, then resumes at the statement after the call.
- Functions can call other functions. They can *not* be nested (defined inside another function) in C++.
- `main()` is the entry point. Every program has exactly one.

## Code in this folder
- `main.cpp` — `main` calls a `greet()` function which itself calls `printSeparator()`, showing the call/return jump.

## Gotchas
- `greet;` (no parens) doesn't call the function — it's an expression naming the function, which the compiler typically warns about and discards.
- You can't define a function inside another function. Define them all at file scope.

## Run
    make 2.01
