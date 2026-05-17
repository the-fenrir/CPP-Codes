# 2.10 — Introduction to the preprocessor

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-the-preprocessor/

## Why it matters
Before the compiler ever sees your code, the preprocessor does a text-substitution pass: includes, macros, conditional compilation. Most "I can't figure out why this won't compile" mysteries in beginner C++ are actually preprocessor-stage problems (double includes, accidentally redefined macros). Knowing what runs *before* the language is half the debugging skill.

## Key points
- The preprocessor operates on **text**, line by line, with no concept of C++ syntax.
- `#include <foo>` (system) and `#include "foo"` (user) — both literally paste the file's contents at the directive.
- `#define NAME value` is a textual macro. Avoid for constants in modern C++ (use `constexpr` instead).
- `#define FLAG` (no value) defines an empty macro — useful with `#ifdef` for feature toggles.
- Conditional compilation: `#ifdef`, `#ifndef`, `#if`, `#else`, `#endif`. Used heavily for header guards (2.12).
- Macros respect no scope rules. They're file-wide from the point of definition until `#undef` or end of TU.

## Code in this folder
- `main.cpp` — `#define`d constant vs. `constexpr`, plus a conditional `#ifdef` block toggled by an empty macro.

## Gotchas
- `#define MAX 10 + 5` then `MAX * 2` expands to `10 + 5 * 2` = `20`, not `30`. Macros don't see expressions.
- Macros are unhygienic — they don't respect namespaces, scopes, or types. `min` and `max` macros from `<windows.h>` famously break `std::min`/`std::max`.
- Includes are textual paste: a `.h` containing `int x{ 0 };` at file scope and included from two TUs = ODR violation.

## Run
    make 2.10
