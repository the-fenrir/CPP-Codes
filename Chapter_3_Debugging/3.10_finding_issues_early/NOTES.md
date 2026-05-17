# 3.10 — Finding issues before they become problems

> learncpp.com: https://www.learncpp.com/cpp-tutorial/finding-issues-before-they-become-problems/

## Why it matters
Everything in 3.1–3.9 is **reactive** debugging — something broke, now diagnose it. This lesson flips: the cheapest bug to fix is the one you never write. A handful of habits move you from "fix bugs in production" to "the compiler / a static analyzer / a unit test catches them on commit."

## Key points
- **Don't make the mistake to begin with.** Most production bugs are typos and copy-paste errors. Smaller functions, single responsibility, and naming that reads aloud are the cheapest preventative measure ever invented.
- **Refactor early.** When code gets gnarly, restructure *without* changing behavior. Bugs hide in complexity; reducing complexity surfaces them. The right time to refactor is *before* you add the feature that would have made the gnarl worse.
- **Defensive programming.** Anticipate misuse: validate inputs, fail loudly on the impossible, return early on bad state. Cheap, and catches the class of bugs where caller-X feeds your-function-Y something it never expected.
- **Test your assumptions** with `assert` (and later, unit tests). An assertion that fires *the first time* you violate it costs five seconds; the bug it would have caused in production costs an afternoon.
- **Use the tools you already have:**
  - Compiler warnings: `-Wall -Wextra -Wpedantic` (this repo's default) — turn on, *read*, and fix every warning. Most real bugs surface as warnings first.
  - Static analyzers: `clang-tidy`, `cppcheck`, the Clang static analyzer. They run without executing your code and catch things compilers don't (null deref through several functions, unreachable code, off-by-one in iteration).
  - Sanitizers: build with `-fsanitize=address,undefined` and run the test suite. Catches uninitialized reads, out-of-bounds, use-after-free, integer overflow at runtime — gives you the file:line for free.
  - Unit tests: GoogleTest, Catch2, doctest. A 5-line test prevents a 5-hour debugging session months later.

## Code in this folder
- `main.cpp` — `safeDivide(a, b)` showing defensive programming (input check + `assert`) and a `static_assert` invariant. Compile, then deliberately violate the precondition and watch the assertion fire.

## Gotchas
- Warnings you've decided to ignore poison the well: real warnings hide in the noise. Either fix them or suppress them surgically with `[[maybe_unused]]` / `#pragma` and a comment explaining why.
- `assert` is compiled out when `NDEBUG` is defined (release builds). Don't put side-effecting calls inside `assert(...)` — they'll silently stop running in release. For checks that must survive release, use a real `if + throw` or your own `ASSERT_ALWAYS`.
- Static analysis with zero suppressions is great. Static analysis with hundreds of "known false positives" suppressed is back to ignored-warning territory.

## Run
    make 3.10
