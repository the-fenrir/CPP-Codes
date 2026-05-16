# 14.14 — Introduction to the copy constructor

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-the-copy-constructor/

## Why it matters
Whenever you write `Foo b = a;` or pass `a` by value, the language runs a **copy constructor** to produce the new object. The compiler generates one for free that copies every member — usually correct. But for classes that own resources (raw pointers, file handles), the default member-wise copy is silently wrong, and you'll need to define your own. The copy constructor is the first slot of the "rule of 0/3/5" you'll meet later.

## Key points
- Signature: `Foo(const Foo& other);` — by `const&` (otherwise it would call itself infinitely).
- Triggered by: `Foo b{ a };`, `Foo b = a;`, pass-by-value, return-by-value.
- Default copy constructor copies each member with *its* copy constructor (member-wise copy).
- For types that hold raw pointers to owned memory, the default does a **shallow copy** — two objects, one buffer, double-free at destruction. Define your own (deep copy) or use smart pointers / RAII types.
- Use `Foo(const Foo&) = delete;` to forbid copying (e.g. for non-copyable resources like file handles).
- Use `Foo(const Foo&) = default;` to ask for the implicit one explicitly.

## Code in this folder
- `main.cpp` — a class with default member-wise copy that works correctly, plus a `= delete` example showing the compile-time block.

## Gotchas
- A copy constructor that takes `Foo` (not `const Foo&`) is a *bug* — infinite recursion at instantiation time.
- "I see no copy happening" — that's usually copy elision (14.15), not absence of the copy constructor. The constructor still has to exist and be accessible.

## Run
    make 14.14
