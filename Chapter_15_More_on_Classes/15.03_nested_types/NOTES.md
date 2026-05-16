# 15.3 — Nested types (member types)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/nested-types-member-types/

## Why it matters
Sometimes a type only makes sense *inside* another type — `LinkedList::Node`, `Image::Pixel`, an enum for a class's own state. Putting these inside the class scopes their names properly, makes the relationship visible to readers, and (with the right access specifier) prevents the rest of the codebase from touching internals.

## Key points
- A class can contain nested **classes**, **enums**, and **type aliases** (`using`/`typedef`).
- Nested type names are accessed with `Outer::Inner`. Inside the outer class body, `Inner` alone is enough.
- Nested types respect access specifiers like data members — `private:` nested types are not visible outside the class.
- A nested **enum** is a great way to give a class strongly-scoped state values (`Door::State::Open`).
- A nested type can refer to its enclosing class (with restrictions on access to its non-static members).

## Code in this folder
- `main.cpp` — `LinkedList<int>`-flavored container with a nested `Node` struct (private) and a public nested `State` enum.

## Gotchas
- A nested class does **not** automatically get access to private members of the enclosing class. It used to *not* have access; since C++11 it *does*. Some compilers' old behavior was the other way; if you target old standards, double-check.
- Nested type aliases (`using value_type = T;`) are the standard-library idiom (`std::vector<T>::value_type`). Use them in your own templates.

## Run
    make 15.03
