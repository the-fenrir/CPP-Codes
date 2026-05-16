# 14.11 — Default constructors and default arguments

> learncpp.com: https://www.learncpp.com/cpp-tutorial/default-constructors-and-default-arguments/

## Why it matters
A **default constructor** is one callable with zero arguments. Without one, `Foo f;` won't compile. Once you declare *any* constructor, the compiler stops generating the default — so you can lose `Foo f;` by accident. Default arguments on a constructor are a cheap way to provide a default constructor and parameterized constructors simultaneously, without the overload explosion.

## Key points
- A default constructor is "one with no parameters, *or* one whose parameters all have defaults."
- If you declare **no** constructors, the compiler generates an implicit default constructor that default-initializes each member.
- If you declare **any** constructor, the implicit one disappears. Re-enable it explicitly with `Foo() = default;`.
- Default arguments on a constructor: `Date(int y = 1970, int m = 1, int d = 1);` — one constructor, callable as `Date{}`, `Date{2025}`, `Date{2025,5}`, `Date{2025,5,16}`.
- **Default member initializers** (in-class init like `int m_x{ 0 };`) work with `= default` to give you a safe zero-state for free.

## Code in this folder
- `main.cpp` — class with a constructor that has all-default args, plus `= default` to keep the compiler-generated default constructor alive.

## Gotchas
- `Foo f();` is still a function declaration, not an object — use `Foo f{};` for default construction.
- Mixing default arguments and constructor overloads can create ambiguity. If you have `Foo()` AND `Foo(int=0)`, the call `Foo{}` is ambiguous. Pick one strategy.

## Run
    make 14.11
