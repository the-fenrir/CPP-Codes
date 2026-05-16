# 14.7 — Member functions returning references to data members

> learncpp.com: https://www.learncpp.com/cpp-tutorial/member-functions-returning-references-to-data-members/

## Why it matters
Returning `const std::string&` from a getter avoids a copy — a real performance win for large members. But the moment the *object* dies, the reference dangles. And if you return a non-const ref, you've handed callers a back door to mutate private state outside any validation. This lesson is half about performance, half about a footgun beginners reliably step on.

## Key points
- Return `const T&` from a getter when `T` is expensive to copy (strings, vectors, etc.).
- Lifetime rule: the reference is only valid while the **owning object** is alive. Don't return a member ref from a function that returns a *temporary* object.
- Returning `T&` (non-const) gives callers write access. Sometimes you want this (`vec[i]`), often you don't.
- In a `const` member function, you may only return `const T&` to a member — not `T&`. The compiler enforces this.

## Code in this folder
- `main.cpp` — getter returning `const std::string&`, plus a dangling-ref example commented out so it actually compiles.

## Gotchas
- `auto x = obj.name();` *copies* even if `name()` returns `const&`. Use `auto& x = obj.name();` to keep it a reference.
- Storing a reference returned by a chain like `getFoo().getBar().getName()` is dangerous — if any link in the chain is a temporary, the reference dangles.
- This sets up 15.10 (ref qualifiers), which lets you forbid getting a reference *from a temporary*.

## Run
    make 14.07
