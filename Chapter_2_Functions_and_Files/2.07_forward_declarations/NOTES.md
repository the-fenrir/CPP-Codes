# 2.7 — Forward declarations and definitions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/forward-declarations/

## Why it matters
C++ compiles a file top-to-bottom. If `main` calls `add` but `add` is defined below, the compiler doesn't know `add` exists yet. Forward declarations tell the compiler "trust me, this symbol exists" so you can structure code in the order that reads best, not in the order the compiler demands. They're also the foundation for splitting code across files (2.8 / 2.11).

## Key points
- A **declaration** introduces a name and its type. A **definition** provides the actual implementation/storage.
- A **forward declaration** (a.k.a. **function prototype**) is a declaration without a body: `int add(int, int);`.
- One Definition Rule (ODR): every function/object has exactly *one* definition across the entire program, but may have many declarations.
- Prototypes may omit parameter names — only the types matter for matching.
- Each function used in a TU must be either defined or declared before it's called.

## Code in this folder
- `main.cpp` — `main` calls `add()` which is defined below; a forward declaration at the top makes it legal.

## Gotchas
- Mismatched prototype and definition (different parameter types) compiles each TU but produces a link error at best, undefined behavior at worst.
- Declaring a function is not the same as defining it; if you declare and never link a definition, the linker fails.
- `int f();` and `int f(void);` mean the same thing in C++ (no parameters). In C they don't — `int f();` in C means "unspecified parameters."

## Run
    make 2.07
