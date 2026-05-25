# 24.5 — Inheritance and access specifiers

> learncpp.com: https://www.learncpp.com/cpp-tutorial/inheritance-and-access-specifiers/

## Why it matters
Two things govern who can see what across an inheritance boundary: the **member's** access (`public`/`protected`/`private`) and the **inheritance mode** (`public`/`protected`/`private`). Get the interaction wrong and you'll either leak implementation or lock derived classes out of state they need.

## Key points
- **Member access**, viewed from the base:
  - `public` — visible everywhere.
  - `protected` — visible to the class and to derived classes, *not* to outside code.
  - `private` — visible only to the class itself (and friends).
- **Inheritance mode** caps how outside code sees inherited members:

  | Member in base | `public` inheritance | `protected` inheritance | `private` inheritance |
  |---|---|---|---|
  | `public`    | `public` in derived    | `protected` | `private` |
  | `protected` | `protected` in derived | `protected` | `private` |
  | `private`   | inaccessible           | inaccessible | inaccessible |

- Rule of thumb: use `public` inheritance. `protected`/`private` inheritance models "implemented in terms of," which is usually composition's job anyway.
- `protected` exists for the case where derived classes legitimately need direct field access — but treat it like a wider `public`: every derived class becomes a coupling point.

## Code in this folder
- `main.cpp` — `Base` with one member at each access level; `Derived` shows which it can read and which the compiler rejects (rejection lines commented out).

## Gotchas
- `private` base members are *inherited* (they're part of the layout) but **not accessible** from the derived class. The compiler is enforcing access, not erasing the storage.
- "Friend of base" doesn't carry into derived. Friendship is per-class.

## Run
    make 24.05
