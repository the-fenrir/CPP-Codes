# 13.4 — Converting an enumeration to and from a string

> learncpp.com: https://www.learncpp.com/cpp-tutorial/converting-an-enumeration-to-and-from-a-string/

## Why it matters
`std::cout << color` prints `0`, not `"red"`. Useful for the compiler, useless for humans. Every project needs to bridge enum values ↔ readable strings: for logging, error messages, config files, and serialization. There's no language feature for it — you write a small function.

## Key points
- The standard pattern: a `getColorName(Color)` function returning a `std::string_view`, implemented with a `switch` over the enumerators.
- Returning `std::string_view` is cheap (no allocation) and safe — the literals it points to have static storage duration.
- For the reverse direction (string → enum), use an `if/else` chain or a lookup table. Validate the input.
- 13.5 will show how to bolt this onto `operator<<` so callers can just `std::cout << color;`.

## Code in this folder
- `main.cpp` — `getColorName` + `colorFromString`, with a small demo.

## Gotchas
- A `switch` over all enumerators without a `default:` will warn if you add a new enumerator and forget to handle it (`-Wswitch`). That's a *feature* — let the compiler remind you.
- If you return a `const std::string&` to a local `std::string`, you get a dangling reference. Return `std::string_view` to a string literal, or return `std::string` by value.

## Run
    make 13.04
