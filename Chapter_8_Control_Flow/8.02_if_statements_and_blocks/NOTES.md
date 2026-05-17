# 8.2 — If statements and blocks

> learncpp.com: https://www.learncpp.com/cpp-tutorial/if-statements-and-blocks/

## Why it matters
`if` is the most basic branch in the language; you'll write it more than anything else in this chapter. The trap is its syntax: by default the `if` and `else` control **exactly one statement**, not "the block underneath." Once you add a second line and don't notice, the program quietly runs that line *unconditionally*. Always-brace style isn't a style fight — it makes the dependency on `if` visible at a glance and is how every serious C++ style guide writes it.

## Key points
- Shape: `if (condition) statement;` or `if (condition) { ... } else { ... }`. The condition is converted to `bool`.
- Without braces, **only the next single statement** is conditional. `if (x > 0) std::cout << "a"; std::cout << "b";` — the second line always runs.
- Braces introduce a **block** (compound statement), which is just "one statement made up of others." Always-brace style — even single-line bodies — prevents the "I added a line later and forgot to brace" bug.
- `else if` is just `else` followed by another `if`. There's no special construct.
- A block opens a **scope** — variables declared inside die at `}`. That's usually what you want: smaller scope = fewer places to misuse the variable.

## Code in this folder
- `main.cpp` — braced vs. unbraced if, an `else if` chain, and the "second statement isn't part of the if" trap shown explicitly.

## Gotchas
- `if (x = 5)` instead of `if (x == 5)` — assignment, not comparison. Always evaluates to truthy. Modern compilers warn (`-Wparentheses`), but it still happens. Some shops write `if (5 == x)` ("Yoda conditions") so a missing `=` is a compile error; opinions differ.
- A semicolon directly after `if (cond);` makes the *empty statement* the body — the next `{ ... }` runs unconditionally. `-Wall` catches it.
- Don't return from an `else` after the `if` already returned. `if (x) return a; else return b;` reads worse than `if (x) return a; return b;` — same control flow, less indentation.

## Run
    make 8.02
