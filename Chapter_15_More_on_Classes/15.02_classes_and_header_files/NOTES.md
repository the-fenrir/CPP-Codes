# 15.2 — Classes and header files

> learncpp.com: https://www.learncpp.com/cpp-tutorial/classes-and-header-files/

## Why it matters
So far every class lived in one `.cpp` file. Real projects need classes visible across files — declarations in a `.h` header, definitions in a `.cpp`. This is the boundary where the language transitions from "toy snippet" to "C++ project." The rules around the One Definition Rule (ODR) and `inline` look weird at first but exist for solid reasons.

## Key points
- **Header (`.h`)**: declares the class — member function signatures, data members. No function bodies (with exceptions, see below).
- **Source (`.cpp`)**: defines the member functions: `void MyClass::foo() { ... }`.
- Always wrap headers with `#pragma once` (or `#ifndef` include guards) to prevent double-inclusion.
- Member functions **defined inside the class body are implicitly `inline`** — multiple translation units may safely include them.
- A non-inline function with a definition in a header **violates ODR** if included from more than one TU — linker error.
- **Templates must be visible at instantiation site**, so class templates and template member functions go *fully in the header* (covered in 15.5).

## Code in this folder
- `point.h` — class declaration with inline accessors.
- `point.cpp` — out-of-line member function definitions.
- `main.cpp` — uses the class.

The Makefile detects header files in the folder and links all `.cpp` together into one binary (instead of compiling each as a standalone target). That's why `make 15.02` builds one program here, not three.

## Gotchas
- Header includes are *textual*. If `a.h` includes `b.h` which includes `a.h`, you'll get a redefinition error without include guards.
- Don't define non-template non-inline functions in headers. Yes, it works "until it doesn't" — until two `.cpp`s include it.
- A `// IWYU-style` mental model: include only what you use; forward-declare when you only need a pointer/reference.

## Run
    make 15.02
