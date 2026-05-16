# 14.5 — Public and private members and access specifiers

> learncpp.com: https://www.learncpp.com/cpp-tutorial/public-and-private-members-and-access-specifiers/

## Why it matters
Access specifiers (`public:`, `private:`, `protected:`) draw the *interface boundary* of a class. Code inside the class can touch anything; code outside can only touch the public bits. This is the actual mechanism of encapsulation — the next three lessons (14.6–14.8) are all about *how* to use it well.

## Key points
- Three specifiers: `public:`, `private:`, `protected:` (protected is for inheritance, covered later).
- Each specifier applies until the next one. Order doesn't matter to the language, but **convention is public first** so readers see the interface before the implementation.
- `class` defaults to `private`, `struct` defaults to `public`.
- Access is **per-class**, not per-object: a `Foo` member function can access the private members of *any* `Foo`, including parameters of type `Foo`.
- Naming convention from learncpp: prefix private data members with `m_` (e.g. `m_value`). Makes private state visually obvious at use sites.

## Code in this folder
- `main.cpp` — class with public interface + private state; demonstrates per-class (not per-object) access.

## Gotchas
- A `public:` block can appear inside a `class` (and vice versa) — repeated specifiers are legal and sometimes useful for readability.
- "Private" is enforced at *compile time only*. `reinterpret_cast` and offsetof can technically reach in. Don't.

## Run
    make 14.05
