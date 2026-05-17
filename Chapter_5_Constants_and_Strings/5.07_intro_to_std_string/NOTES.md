# 5.7 — Introduction to `std::string`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring/

## Why it matters
C-strings (`char[]`, `const char*`) are the original C++ string type and they're a constant source of bugs: manual length tracking, no bounds checking, no concatenation operator, no `==`. `std::string` is the modern replacement — it owns its characters, grows automatically, knows its own length, and works with the operators you'd expect. Use it by default; reach for `const char*` only when an API demands it.

## Key points
- `#include <string>`. The type lives in `std::`.
- Initialize from a string literal: `std::string name{ "Alice" };`. Assign with `=`. Concatenate with `+` or `+=`. Compare with `==`, `!=`, `<`, etc. — *value* comparison, not pointer comparison.
- `.length()` and `.size()` are synonyms and return the character count (not including the null terminator). They run in O(1).
- **Input.** `std::cin >> s;` reads a single whitespace-delimited token. To read a full line (including spaces), use `std::getline(std::cin, s);`.
- **The `>>` / `getline` mix-up.** If you do `std::cin >> n;` and then `std::getline(std::cin, s);`, the `getline` reads the empty leftover newline. Fix with `std::cin >> std::ws` or `std::cin.ignore(...)` between them.
- **Passing strings.** Prefer `const std::string&` for parameters that already are `std::string`s. Prefer `std::string_view` (5.8) for parameters that just need to *read* characters from any string-like source.
- `std::string` owns its storage on the heap (with small-string optimization). Copies allocate; moves don't. Returning by value is fine — copy elision + moves handle it.

## Code in this folder
- `main.cpp` — construction, concatenation, comparison, `length()`, `getline` (with the `>>`-then-`getline` fix shown), and pass-by-`const&`.

## Gotchas
- `std::string s{ 65 };` does *not* create the string "65". It calls the `size_t, char` constructor and gives you a string of 65 null bytes (or worse, depending on overload). Use `std::to_string(65)` or `s = std::to_string(65);`.
- `s1 + s2` allocates a new string. In hot loops, `s1 += s2;` (or `s1.append(...)`) avoids the temporary.
- `std::cin >> s` stops at the first whitespace. `"Alice Smith"` becomes just `"Alice"`. Use `std::getline`.

## Run
    make 5.07
