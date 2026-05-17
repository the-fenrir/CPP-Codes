# 4.11 — Chars

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chars/

## Why it matters
`char` is the type for a *single* character — letter, digit, symbol, space. It's also an integer in disguise: a `char` holds the numeric ASCII code of the character it represents. That dual nature is why you can do `'A' + 1 == 'B'` and why printing a `char` integer prints the letter, not the number.

## Key points
- `char` is exactly 1 byte. Whether it's signed or unsigned by default is **implementation-defined** — don't rely on it. Use `signed char` / `unsigned char` explicitly when the sign matters.
- ASCII: codes 0–31 are control characters, 32 is space, 48–57 are `'0'`–`'9'`, 65–90 are `'A'`–`'Z'`, 97–122 are `'a'`–`'z'`.
- **Single quotes** denote a `char` literal: `'A'`. **Double quotes** denote a string literal: `"A"` (which is a 2-character array including the null terminator).
- `std::cout << ch` prints `ch` as a character. To print its numeric value, `static_cast<int>(ch)`.
- `std::cin >> ch` skips leading whitespace and reads one character. To read a whitespace character (including newline), use `std::cin.get(ch)`.
- Escape sequences: `'\n'` newline, `'\t'` tab, `'\\'` backslash, `'\''` single quote, `'\"'` double quote, `'\0'` null terminator, `'\r'` carriage return.

## Code in this folder
- `main.cpp` — char ↔ int duality, arithmetic on chars, escape sequences, and the single- vs double-quote distinction.

## Gotchas
- `char ch{ 65 };` stores the integer 65. `std::cout << ch;` prints `A`. `std::cout << static_cast<int>(ch);` prints `65`. Both are correct — pick based on what you want to *show*.
- Multi-character literals like `'AB'` are legal but implementation-defined (and usually pointless). Stick to one character per single-quoted literal.

## Run
    make 4.11
