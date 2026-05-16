# 14.4 — Const class objects and const member functions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/const-class-objects-and-const-member-functions/

## Why it matters
`const` on a class object means "don't mutate me." But the compiler doesn't *trust* you — it enforces it by only allowing **const member functions** to be called. Without `const`-correct member functions, your class becomes unusable to anyone passing it as `const T&`, which is the default way C++ takes objects in function parameters. Get this wrong and your class is *infectious*.

## Key points
- A `const` object can only call member functions marked `const`.
- Mark a member function `const` by suffixing the signature: `void print() const;`
- A `const` member function **may not modify** any non-mutable data member or call any non-const member function.
- Rule of thumb: every member function that doesn't logically modify the object should be `const`. Default to `const`; make exceptions.
- `const` is part of the function signature for overloading — you can have both `T& get()` and `const T& get() const`.

## Code in this folder
- `main.cpp` — same class, with and without `const` member functions; shows the compile error a non-const method causes on a const object.

## Gotchas
- A `const` member function gets a `const T*` `this` pointer — so even non-pointer members appear const-qualified inside.
- `mutable` lets a member be modified even inside a `const` method. Use it sparingly (caches, lazy-init).
- Returning a pointer/reference to a non-const member from a const method silently launders away the const. (Lesson 14.7 covers this footgun directly.)

## Run
    make 14.04
