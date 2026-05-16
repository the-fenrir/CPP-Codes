# 14.8 — The benefits of data hiding (encapsulation)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/the-benefits-of-data-hiding-encapsulation/

## Why it matters
Why bother with all this `private:` + getters/setters ceremony? Because **encapsulation = the freedom to change the implementation without breaking callers.** That payoff isn't visible in toy examples; it shows up six months later when you want to rename a member, change its type, add validation, or compute it on the fly. With a public field, you can't. With a private field behind a function, you can.

## Key points
- Encapsulation gives you: **(1) invariants** the class can enforce, **(2) freedom to refactor** internals, **(3) a stable interface** for callers.
- The interface is the *public member functions*; the implementation is everything else. Callers should only know the interface.
- "Encapsulation" is broader than `private:`. It's the design *discipline* of hiding implementation details. Marking a field private with a get/set pair that exposes it 1:1 is encapsulation in name only.
- Good encapsulation often means **fewer** public functions, not more — model operations the caller actually performs.

## Code in this folder
- `main.cpp` — `Stack` whose internal storage type changes between two versions without touching the calling code.

## Gotchas
- Premature encapsulation is a real cost. Plain data bags (`struct Point { double x, y; };`) should stay plain.
- Public *member functions* are also part of the interface — adding one is cheap; *removing* one breaks callers. Be deliberate.

## Run
    make 14.08
