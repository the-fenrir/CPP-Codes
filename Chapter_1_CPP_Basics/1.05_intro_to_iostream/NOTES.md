# 1.5 — Introduction to iostream: cout, cin, endl

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-iostream-cout-cin-and-endl/

## Why it matters
A program that can't talk to the outside world isn't very useful. `<iostream>` is the standard library's front door for terminal I/O. Knowing `cout`, `cin`, `endl`, and `'\n'` covers 90% of what you need for the next dozen chapters.

## Key points
- `#include <iostream>` to use any of the below.
- **`std::cout`** + the **insertion operator** `<<` — output: `std::cout << "hi";`
- **`std::cin`**  + the **extraction operator** `>>` — input:  `std::cin  >> x;`
- Chain insertions: `std::cout << "x = " << x << '\n';`
- **`std::endl`** writes a newline **and** flushes the output buffer.
- **`'\n'`** writes a newline only. Prefer it — flushing on every line is needlessly slow.

## Code in this folder
- `main.cpp` — reads an integer from the user and echoes it back.

## Gotchas
- `'\n'` (char literal) and `"\n"` (string literal) both work with `<<`, but `'\n'` is conventionally cheaper.
- If `std::cin >> x;` fails (user typed non-numeric input), `cin` enters a fail state and subsequent reads silently do nothing. Robust input handling comes much later (Chapter 7+).

## Run
    make 1.05
