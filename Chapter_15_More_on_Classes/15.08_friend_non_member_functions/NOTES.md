# 15.8 — Friend non-member functions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/friend-non-member-functions/

## Why it matters
Sometimes a function logically belongs *with* a class but can't be a member — most famously, `operator<<` for streaming, where the left-hand operand must be `std::ostream&`. `friend` lets you grant such non-member functions access to your private members while keeping them out of the class's interface. Use it sparingly — friendship is a hole in your encapsulation, but a hole you opened on purpose.

## Key points
- `friend` is declared *inside* the class, granting access to a function that's not a member.
- The friend declaration is **not** itself a member — access specifier where it lives doesn't matter (place it anywhere in the class for clarity).
- Friendship is **not symmetric** (Foo friending Bar doesn't make Bar friend Foo) and **not transitive**.
- Common cases: stream operators (`operator<<`, `operator>>`), binary operators where neither operand should be the LHS member.
- Less is more. If a function can be implemented with public members only, don't make it a friend.

## Code in this folder
- `main.cpp` — `Money` class with a friend `operator<<` that streams its private state.

## Gotchas
- A friend function declared *inside* the class is *not* automatically `inline` — its definition still goes either in the header (with `inline`) or in a .cpp.
- Adding a friend changes ABI of the class only minimally, but adds an item to the "who depends on private internals" list. Track that list.

## Run
    make 15.08
