# 10.2 — Floating-point and integral promotion

> learncpp.com: https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/

## Why it matters
Hardware is fastest at its native word size (typically `int` and `double`). Smaller types (`char`, `short`, `float`) often have to be widened before the CPU can compute on them. C++ formalizes this as **promotion**: an implicit, **value-preserving** conversion to a wider type. Every original value still has a unique, exact representation in the destination — no information lost.

## Key points
- **Integral promotion**: any integer type *narrower than `int`* (`bool`, `char`, `signed char`, `unsigned char`, `short`, `unsigned short`) is promoted to `int` (or `unsigned int` if `int` can't hold all its values).
- **Floating-point promotion**: `float` promotes to `double`.
- Promotion happens at expression evaluation: `short s = 1; auto x = s + s;` — `x` is `int`, not `short`.
- Promotion is always safe — that's why the standard does it for you.
- Promotion is *not* the same as "numeric conversion" (10.03). Conversion may lose value; promotion never does.

## Code in this folder
- `main.cpp` — uses `typeid` to expose the result type of expressions involving small integer / float operands.

## Gotchas
- `char c = 'A'; std::cout << c;` prints `A`. But `std::cout << c + 0;` prints `65`, because `+` promotes `c` to `int` and there's no `char` overload picked.
- Promotion is one-way: you can promote `short → int`, but the reverse is a numeric conversion (potentially narrowing).
- The result of `short + short` is `int`. Assigning back to `short` is itself a narrowing conversion.

## Run
    make 10.02
