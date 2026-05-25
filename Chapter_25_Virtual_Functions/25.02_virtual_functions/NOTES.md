# 25.2 — Virtual functions and polymorphism

> learncpp.com: https://www.learncpp.com/cpp-tutorial/virtual-functions/

## Why it matters
The fix for 25.01's "Base& sees Base's version" problem. Mark a member function `virtual` in the base, and a call through `Base&`/`Base*` is resolved at runtime to the most-derived override — the entire mechanism that the word "polymorphism" usually refers to in C++.

## Key points
- `virtual ReturnT name(Args...)` in the base. Derived class redeclares the **same signature** to override; the keyword is optional on the override but should be communicated via `override` (25.03).
- "Same signature" = same name, parameter list, and const/ref qualifiers. Mismatch silently creates an *overload*, not an override — which is why `override` exists.
- Return type must match (or be covariant — 25.03).
- Once a function is virtual in some base, it's virtual in every derived class regardless of whether the keyword is repeated.
- Cost: each virtual call goes through the vtable — one extra pointer indirection (25.06). Negligible in almost all real code; not zero.

## Code in this folder
- `main.cpp` — same Animal/Cat/Dog hierarchy as 25.01, but `speak()` is `virtual`. Now `describe(const Animal&)` correctly says "Meow" / "Woof".

## Gotchas
- A non-virtual function in a derived class with the same signature **hides** the base's, it does not override. You'll learn this the hard way at least once.
- Calling a virtual function from inside a constructor or destructor resolves to the *current* class's version — the derived object isn't fully alive yet (or is already partly dead). Don't.
- Default argument values are determined statically (from the static type), so don't put defaults on virtual functions — they don't behave the way you expect.

## Run
    make 25.02
