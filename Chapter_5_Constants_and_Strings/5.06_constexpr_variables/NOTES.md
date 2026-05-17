# 5.6 — Constexpr variables

> learncpp.com: https://www.learncpp.com/cpp-tutorial/constexpr-variables/

## Why it matters
`const` says "I won't change this." `constexpr` says "the compiler must be able to figure this out at compile time, and the compiler will *enforce* that." It's the strongest form of constness available for variables: the value lives in the binary, it can be used as an array size or template argument, and any expression you try to initialize it with that isn't compile-time evaluable becomes a compile error.

## Key points
- `constexpr T name{ value };` — the initializer **must** itself be a constant expression. The compiler refuses to compile otherwise. This is the headline difference from `const`.
- `constexpr` implies `const`. You don't need both; redundant.
- Works for any *literal type*: integers, floats, `bool`, `char`, enum, plain pointers, and (since C++17) certain user-defined types whose constructor is `constexpr`. `std::string` is *not* a literal type pre-C++20, and only conditionally so in C++20 — prefer `constexpr std::string_view` for compile-time string constants.
- **Rule of thumb**: if a value is known when you write the code and never depends on runtime input, prefer `constexpr` over `const`. It's free at runtime and the compiler will tell you when you're wrong.
- For function-local "magic numbers" with domain meaning, `constexpr` is the right default. For things derived from user input or files, plain `const` is the only option.

## Code in this folder
- `main.cpp` — `constexpr` with various literal types, `constexpr` failing on a non-constant initializer (commented), and a `constexpr std::string_view`.

## Gotchas
- `constexpr int n{ getInput() };` is a compile error. That's the *point* — if you wanted runtime, use `const`.
- `constexpr` on a pointer constrains the pointer, not the pointee: `constexpr int* p{ &x };` — `p` is the constant, `*p` is still mutable. For "pointer to const int", you want `constexpr const int* p{ &x };`.
- A `constexpr` function isn't the same as a `constexpr` variable (covered later in the book). A `constexpr` function *can* be evaluated at compile time when its inputs are constant expressions.

## Run
    make 5.06
