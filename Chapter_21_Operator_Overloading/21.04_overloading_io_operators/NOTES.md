# 21.4 — Overloading `operator<<` and `operator>>`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/overloading-the-io-operators/

## Why it matters
`std::cout << point` looks like a method call on `cout`. That's because it *is* one — `operator<<` is a member of `std::ostream`. You can't add member functions to `std::ostream`, so to make your class streamable you write a **non-member** `operator<<` whose left operand is `std::ostream&` and right operand is your type. Same shape for `operator>>` with `std::istream&`.

## Key points
- Signature: `std::ostream& operator<<(std::ostream& out, const T& obj);` Return the stream — that's what makes chaining (`cout << a << b;`) work.
- Mirror form: `std::istream& operator>>(std::istream& in, T& obj);` (note `T&`, not `const T&` — you're filling it in).
- `friend` it inside the class **only if** it needs private access. If your class has accessors, prefer plain non-member.
- For `operator>>`: set a fail state explicitly with `in.setstate(std::ios_base::failbit);` if parsing failed, so callers can detect it via `if (cin >> x)`.

## Code in this folder
- `main.cpp` — a `Point` class with `<<` and `>>` as friend functions. Demonstrates chaining and reading from `std::istringstream`.

## Gotchas
- Returning anything other than `std::ostream&` (e.g. returning `void`) kills chaining and is non-standard. Always return the stream by reference.
- Don't print a trailing newline from `operator<<`; the caller decides line endings.
- If you only need to print, prefer overloading `<<` over adding a `print()` member. It composes with the standard I/O machinery (`std::format` in C++20+, `<<` chaining, formatting flags).

## Run
    make 21.04
