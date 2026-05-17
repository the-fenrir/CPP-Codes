# 12.5 — Pass by lvalue reference

> learncpp.com: https://www.learncpp.com/cpp-tutorial/pass-by-lvalue-reference/

## Why it matters
Pass-by-value copies the argument. Cheap for `int`, expensive for `std::string` or `std::vector`, and impossible for non-copyable types. Pass-by-(non-const)-reference avoids the copy *and* lets the function modify the caller's object — making it the standard mechanism for "in/out" parameters.

## Key points
- Syntax: `void f(T& param)`. Inside `f`, `param` is an alias for whatever was passed.
- No copy is made. Modifications inside `f` are visible to the caller.
- The argument must be a **modifiable lvalue** — you can't pass a literal, rvalue, or const object to `T&`.
- Cheap for *any* type (a reference is roughly the size of a pointer), so larger types benefit more than small ones — but a small type passed by value avoids one level of indirection and is usually preferred.
- The function's signature *documents* the side-effect: a non-const reference parameter is a contract that says "I may modify this."

## Code in this folder
- `main.cpp` — a `swap` and an `increment`. Compare the call sites.

## Gotchas
- Easy to miss at the call site: `increment(x);` looks identical to `print(x);`, but one mutates `x` and the other doesn't. Reader has to know the signature.
- Don't use `T&` *just* to avoid copying — use `const T&`. Non-const reference parameters should be reserved for genuine in/out semantics.
- Cannot pass an rvalue: `increment(x + 1);` fails to compile, which is usually what you want (it'd be modifying a temporary).

## Run
    make 12.05
