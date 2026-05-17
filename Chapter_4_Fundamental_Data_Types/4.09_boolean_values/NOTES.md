# 4.9 — Boolean values

> learncpp.com: https://www.learncpp.com/cpp-tutorial/boolean-values/

## Why it matters
`bool` is the type of `if`/`while` conditions, of comparison results, and of every yes/no question your program asks. Knowing how it converts to/from integers, and how to print and read it as text, makes I/O code straightforward.

## Key points
- Type: `bool`. Values: `true`, `false`. Operators: `!` (not), `&&` (and), `||` (or).
- Internally stored as integer `1` (true) or `0` (false). `sizeof(bool)` is typically 1 byte.
- **Output**: default prints `1` / `0`. `std::cout << std::boolalpha` switches to `true` / `false` (sticky); `std::noboolalpha` switches back.
- **Input**: by default `std::cin` reads `0` / `1`. After `std::cin >> std::boolalpha`, it reads the lowercase words `true` / `false` instead — and numeric input then fails. Pick one mode per stream.
- **Integer → bool conversion**: `0` becomes `false`, anything else becomes `true`. So `if (x)` reads "if x is non-zero." Brace-init narrows: `bool b{ 2 };` is an error; `bool b = 2;` is allowed and produces `true` (with a warning under `-Wconversion`).
- Conventional naming: predicate functions / boolean variables read as questions — `isValid`, `hasNext`, `canRetry`.

## Code in this folder
- `main.cpp` — boolalpha, integer-to-bool conversion, and `!`/`&&`/`||` truth tables in tiny form.

## Gotchas
- `if (x = 5)` (assignment) compiles, evaluates the assigned value as bool, and is almost always a bug for `if (x == 5)`. Many compilers warn; trust the warning.
- Don't write `if (b == true)`. It's `if (b)`. The redundant comparison is a smell.

## Run
    make 4.09
