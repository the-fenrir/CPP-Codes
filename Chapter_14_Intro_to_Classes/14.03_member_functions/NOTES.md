# 14.3 — Member functions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/member-functions/

## Why it matters
Free functions take the object as a parameter; **member functions** are called *on* the object and have implicit access to its data. This is the mechanism behind `obj.doThing()` and the foundation for the OO style you saw in 14.1. Member functions also know which object they're acting on (via the hidden `this` pointer, formalized in 15.1).

## Key points
- Defined inside the class body, or inside the body declared and outside it defined with `ClassName::funcName`.
- Inside a member function, member names refer to the current object's members — no `this->` needed (but legal).
- Member functions can be **overloaded** like free functions.
- **Order independence inside a class:** a member function can refer to a member declared *later* in the class. That's not true for free functions.
- Member functions don't add to `sizeof(Class)` — they're not stored per-object.

## Code in this folder
- `main.cpp` — `Date` with member functions, plus a member function defined outside the class.

## Gotchas
- Defining a member function inside the class body makes it implicitly `inline` (matters in 15.2 when you split header/source).
- "I called a member function but it printed garbage" — usually means you forgot to initialize the data members. Coming up in 14.9.

## Run
    make 14.03
