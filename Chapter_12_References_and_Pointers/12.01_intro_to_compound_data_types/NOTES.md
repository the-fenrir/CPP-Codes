# 12.1 — Introduction to compound data types

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-compound-data-types/

## Why it matters
Chapters 4–6 covered the **fundamental** types (`int`, `double`, `char`, `bool`). They're enough for arithmetic but not enough to model anything real: a position needs three coordinates, a name needs a sequence of characters, a "maybe a value" needs to express absence. **Compound types** are types built out of other types — references, pointers, arrays, structs, classes, enums. This chapter starts with the two simplest: references and pointers.

## Key points
- A **compound type** is constructed from a fundamental type or another compound type.
- The C++ compound type families: functions, arrays, pointer types, pointer-to-member types, reference types, enumerated types, class types.
- We've already used compound types informally: `std::string` (class), function types (every function you've written).
- This chapter focuses on **references** (alias for an existing object) and **pointers** (an object whose value is a memory address).
- Both let one name refer to an object that lives elsewhere — but with very different rules around nullability, rebinding, and syntax.

## Code in this folder
- `main.cpp` — a tour: fundamental type, then a reference to it, then a pointer to it, side by side.

## Gotchas
- "Compound" doesn't mean "complicated." A reference is still one of the simplest things in C++ — it's literally just another name for an existing object.
- Don't confuse a compound *type* with a compound *statement* (the `{ ... }` block). Different concept, same word.

## Run
    make 12.01
