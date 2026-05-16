# 14.10 — Constructor member initializer lists

> learncpp.com: https://www.learncpp.com/cpp-tutorial/constructor-member-initializer-lists/

## Why it matters
A constructor body runs *after* all members are constructed. So if you write `m_x = y;` in the body, you've already paid for default-construction and now you're paying again for assignment. Worse, **const and reference members can't be assigned at all** — they must be initialized. The **member initializer list** is the one place where you *initialize* members, before the body runs. It is the correct way to set member values, full stop.

## Key points
- Syntax: `Foo(int x, int y) : m_x{ x }, m_y{ y } { /* body */ }`
- Initializer list runs *before* the constructor body. Body assignment is a fallback you usually don't want.
- **Required** for: `const` members, reference members, base-class initialization, members that have no default constructor.
- **Order matters:** members are initialized in the order they're *declared in the class*, NOT the order they appear in the initializer list. Compilers warn on mismatch — believe the warning.
- One member's initializer can use another member only if the *other* is declared earlier.

## Code in this folder
- `main.cpp` — same `Date` as 14.9, rewritten with an initializer list; plus a const member showing why it's not optional.

## Gotchas
- Don't initialize a member from another member that's *declared after it* in the class. Even if it looks right textually, the order is by declaration.
- Prefer the brace `{}` form in initializer lists — disallows narrowing conversions.

## Run
    make 14.10
