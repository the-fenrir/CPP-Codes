# 15.9 — Friend classes and friend member functions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/friend-classes-and-friend-member-functions/

## Why it matters
You can friend an entire **class** (giving all its member functions access to your privates) or a **specific member function** of another class (more surgical). The classic case: a tightly-coupled helper class — `Tree` and `TreeIterator`, `Document` and `DocumentSerializer`. Done right, this is a controlled coupling; done wrong, it's encapsulation laundered through paperwork.

## Key points
- **Friend class:** `friend class Bar;` inside `Foo` makes every member of `Bar` able to access `Foo`'s privates.
- **Friend member function:** `friend void Bar::baz();` grants only `Bar::baz()` access. Requires `Bar` to be defined (or forward-declared with enough detail) before the friend declaration.
- Friendship is **declared by the granter**, not requested by the friend. The class with the secrets controls who sees them.
- Mutual access: each class friends the other (this is sometimes warranted but usually a smell).
- Prefer the narrowest friendship: a single function > a single class > "everyone in this header."

## Code in this folder
- `main.cpp` — `Vault` with a friend class `Auditor` that can peek inside.

## Gotchas
- Forward declaration is often required: `class Bar;` before `class Foo { friend class Bar; … };`.
- Friend declarations don't cross **inheritance** — a class derived from a friend is not itself a friend.

## Run
    make 15.09
