# 1.11 — Developing your first program

> learncpp.com: https://www.learncpp.com/cpp-tutorial/developing-your-first-program/

## Why it matters
This lesson pulls together everything from 1.1–1.10 into one small interactive program. The deeper lesson is the **process**: write a little, compile, run, then add the next slice. "Compile and run after every meaningful change" is the single most important habit in C/C++.

## Key points
- Stitch together: `#include`, `main`, variables, `cin`, `cout`, expressions.
- Build incrementally — write the smallest thing that compiles, then extend.
- Compile often. A diff of one working version against the next is easier to debug than a 200-line block that doesn't build.
- Get it *working* first, then make it *clean* (rename, factor, comment). Don't polish broken code.

## Code in this folder
- `main.cpp` — doubles a number. To stay non-interactive under `make`, the input value is hard-coded; the commented-out `std::cin >> x;` line shows what the interactive version would look like.

## Gotchas
- `std::cin >> x` for an `int` fails silently if the user types text. Handle that properly later (Chapter 7+).
- A program that "works on my one test input" is not a program that works. Try edge cases (0, negative, large) even at this scale.

## Run
    make 1.11
