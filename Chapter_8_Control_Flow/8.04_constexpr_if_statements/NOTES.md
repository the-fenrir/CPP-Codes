# 8.4 — Constexpr if statements

> learncpp.com: https://www.learncpp.com/cpp-tutorial/constexpr-if-statements/

## Why it matters
A regular `if` decides at **runtime** which branch to run — both branches must compile, both end up in the binary. `if constexpr` (C++17) decides at **compile time**: the not-taken branch is *discarded entirely*, before semantic checks. That sounds like a micro-optimization, but its real payoff is in templates, where one branch may not even be *valid* code for a given type. It also produces a tiny but free speedup when a condition is known at compile time, by skipping a dead branch from the binary.

## Key points
- Syntax: `if constexpr (constant-expression) { ... } else { ... }`. The condition must be a constant expression.
- The branch not taken is **discarded**: it's not compiled into the binary, and many semantic errors inside it are suppressed (because the compiler never instantiates them).
- The typical use is in templates: a single function template that "does something different for ints vs. floats vs. strings" by switching on `if constexpr (std::is_integral_v<T>)`.
- For a non-template function, `if constexpr` and a regular `if` behave the same at runtime — the compiler can already optimize a constant `if` away. The semantic difference matters once both branches aren't valid for all instantiations.
- Don't write `if constexpr` "just in case." Use it when (a) the condition is genuinely compile-time and (b) the not-taken branch wouldn't otherwise compile.

## Code in this folder
- `main.cpp` — a function template `describe<T>(T)` that uses `if constexpr` to branch on `std::is_integral_v<T>` / `std::is_floating_point_v<T>`. Each branch contains code that would *not* compile for the other type.

## Gotchas
- The condition has to actually be a constant expression. A `const` runtime value isn't a constant expression — see 5.5.
- `if constexpr` is a C++17 feature. Set `-std=c++17` or later. This repo uses C++20.
- It doesn't make the *body* constexpr, only the choice of branch. Runtime statements still execute at runtime.

## Run
    make 8.04
