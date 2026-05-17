# 1.1 — Statements and the structure of a program

> learncpp.com: https://www.learncpp.com/cpp-tutorial/statements-and-the-structure-of-a-program/

## Why it matters
A C++ program is a sequence of **statements** grouped into **functions**. Before you can read or write any code, you need to know what counts as one "instruction," where it lives, and why every program must contain a function named `main`. This lesson is the grammar floor under everything else.

## Key points
- A **statement** is the smallest standalone instruction. Most end with `;`.
- Statements live inside **functions**. A function is a named block of statements.
- Every executable C++ program must have exactly one function named `main` — that's where execution starts.
- `#include <iostream>` is a **preprocessor directive**, not a statement (no semicolon).
- `return 0;` from `main` signals "success" to the OS. C++ lets you omit it; the compiler implies `return 0;`.

## Code in this folder
- `main.cpp` — minimal "Hello, world" annotated with the role of each line.

## Gotchas
- Preprocessor directives (`#include`, `#define`) start with `#` and do **not** take a semicolon. Adding one is a common beginner error.
- `main` must return `int`. `void main()` is non-standard C++ even if some old compilers accept it.

## Run
    make 1.01
