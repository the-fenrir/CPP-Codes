# 12.6 — Pass by const lvalue reference

> learncpp.com: https://www.learncpp.com/cpp-tutorial/pass-by-const-lvalue-reference/

## Why it matters
`const T&` is the default parameter type in C++ for any input that isn't a tiny built-in. It gives you the cost of pass-by-pointer with the syntax of pass-by-value, accepts literals/temporaries thanks to lifetime extension, and tells the reader "I won't modify this."

## Key points
- Signature: `void f(const T& param)` — no copy, no mutation, accepts everything readable.
- Use for: any input parameter where `T` is non-trivially copyable (strings, vectors, classes).
- For tiny types (`int`, `double`, pointer, small structs): pass by value. The extra indirection from a reference is more expensive than the copy and worse for the optimizer.
- Rough cutoff: if `sizeof(T) <= sizeof(void*)` and `T` is trivially copyable, pass by value; otherwise pass by `const T&`.
- A `const T&` parameter accepts: const objects, non-const objects, rvalues, temporaries, conversions. The most permissive input type.

## Code in this folder
- `main.cpp` — `printPerson(const std::string&)` vs. by-value, showing the call site is identical.

## Gotchas
- `const T&` to a *temporary of a different type* still creates a hidden temporary. `void f(const std::string&);` called as `f("hi")` materializes a `std::string` from the C-string — fine, but be aware it's not free.
- Don't `const T&` everywhere blindly. For `int`, `char`, pointers — pass by value.
- A function taking `const T&` that just immediately copies its argument is wasted work — if you need a copy anyway, take it by value and use the copy directly (this is the "pass-by-value-then-move" idiom that shows up later).

## Run
    make 12.06
