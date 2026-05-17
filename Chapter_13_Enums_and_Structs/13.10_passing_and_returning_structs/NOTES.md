# 13.10 — Passing and returning structs

> learncpp.com: https://www.learncpp.com/cpp-tutorial/passing-and-returning-structs/

## Why it matters
A struct holds a bundle of data — and copying that bundle on every function call costs real cycles. The rules-of-thumb here are the same as for `std::string`/`std::vector`: pass by `const&` when the function doesn't modify, return by value (RVO/copy elision makes it free).

## Key points
- **Pass by `const T&`** when the function only reads. Avoids the copy; the `const` says "I won't mutate it."
- **Pass by `T&`** when the function modifies the caller's object.
- **Pass by value** only for tiny structs (one or two cheap members). Below ~16 bytes, by-value is often *cheaper* than by-ref because it skips an indirection.
- **Return by value.** Don't return `T&` to a local — it dangles. C++17 mandates copy elision for prvalues, so `return Fraction{ a, b };` costs nothing.
- This is where the chapter introduces the `Fraction` struct that Chapter 14's quiz turns into a class. The signatures `getFraction()`, `multiply(const Fraction&, const Fraction&)`, `printFraction(const Fraction&)` are the canonical version.

## Code in this folder
- `main.cpp` — `Fraction` struct with `getFraction`, `multiply`, `printFraction`. Same signatures the Chapter 14 quiz starts from.

## Gotchas
- Returning a `const T&` to a local is undefined behavior. Return by value or `T` (not `T&`).
- Pass-by-value of a `std::string`-containing struct is *not* trivial — it copies the string. Use `const&` unless you really want the copy.

## Run
    make 13.10
