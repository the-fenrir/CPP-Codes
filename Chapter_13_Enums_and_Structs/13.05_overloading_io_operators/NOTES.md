# 13.5 — Introduction to overloading the I/O operators

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-overloading-the-i-o-operators/

## Why it matters
`std::cout << foo` should "just print foo," whatever `foo` is. To make that work for *your* type, you give the language one new overload of `operator<<`. Same for `operator>>`. After this, every callsite reads naturally and you stop having to remember function names like `printColor`.

## Key points
- `operator<<` overload signature: `std::ostream& operator<<(std::ostream& out, T value)` (or `const T&`). Return `out` so chaining works.
- `operator>>` overload signature: `std::istream& operator>>(std::istream& in, T& value)`. The second parameter is non-const ref — you're filling it in.
- These overloads are **free functions**, not member functions, because the left operand is `std::ostream`/`std::istream` (we don't own those types). For struct/class types in later chapters they're often **`friend`**s.
- For unscoped enums, the body is usually `return out << getColorName(value);` (delegates to 13.4's helper).
- `operator>>` for an enum: read an `int` (or string), validate range, set the output param, set `in.setstate(std::ios_base::failbit)` if the input was invalid.

## Code in this folder
- `main.cpp` — overloads `operator<<` and `operator>>` for a `Color` enum, demoing both `std::cout` and a `std::stringstream` input.

## Gotchas
- Forgetting to `return out;` makes chained `cout << a << b` fail to compile in a hard-to-read way.
- Don't overload `operator<<` as a member of `std::ostream` (you can't), or as a member of your type (left operand wouldn't be your type). Free function.

## Run
    make 13.05
