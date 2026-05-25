# 25.7 — Pure virtual functions, abstract base classes, and interface classes

> learncpp.com: https://www.learncpp.com/cpp-tutorial/pure-virtual-functions-abstract-base-classes-and-interface-classes/

## Why it matters
Sometimes a base has no sensible default implementation — "what does it mean to `Animal::speak()` for a generic animal?" Pure virtuals say "there *is* no default; derived must provide one." This turns the base into an **abstract class** that can't be instantiated, only inherited from — the standard way to express "this is a role, not a thing."

## Key points
- Syntax: `virtual ReturnT name(Args...) = 0;`. The `= 0` makes it pure virtual.
- A class with one or more pure virtuals is **abstract**: you cannot create instances of it directly. You *can* still have pointers and references to it.
- Derived classes must override every pure virtual to themselves become concrete. Otherwise they're abstract too.
- A pure virtual may still have a definition (`= 0` and a body) — derived must still override, but can chain to the base implementation via `Base::name()` (see 25.04).
- An **interface class** is the special case: a class containing only pure virtual functions and no member variables, used to express "any type that can do these things." Pair with a virtual destructor.

## Code in this folder
- `main.cpp` — `Animal` is abstract with a pure virtual `speak()`; `Cat` and `Dog` make it concrete. Plus an `IPrintable` interface and a couple of unrelated types that implement it, demonstrating "interface as contract."

## Gotchas
- A pure virtual destructor is legal and useful when you want an abstract class with no other pure-virtual members. **You must still provide a definition** (`Base::~Base() = default;` after the declaration). The derived destructor will chain into it.
- Forgetting to override one pure virtual in a derived class makes that derived class also abstract — and the compile error appears at the *use* site (`new Derived`), not the class definition. Read carefully.
- "Interface class" isn't a C++ keyword — it's a convention. Some codebases mark them with a leading `I` (`IPrintable`), some don't.

## Run
    make 25.07
