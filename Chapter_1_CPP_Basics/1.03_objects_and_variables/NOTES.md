# 1.3 — Introduction to objects and variables

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-objects-and-variables/

## Why it matters
Programs manipulate data, and data lives in memory. A **variable** is a named region of memory of a specific type. Naming and typing data is how you stop thinking in raw bytes and start thinking in concepts ("a count," "a price").

## Key points
- **Object** (in the C++ memory sense, not OOP): a region of memory with a type that holds a value.
- **Variable**: a named object.
- **Definition** introduces a variable: `int x;` — reserves storage of type `int` under the name `x`.
- **Data type** tells the compiler how to interpret the bits (e.g. `int` ⇒ a signed integer).
- You can define multiple variables of the same type on one line: `int a, b;` — works, but most style guides discourage it for readability.

## Code in this folder
- `main.cpp` — defines a few variables and prints them.

## Gotchas
- Defining a variable does **not** initialize it. `int x;` leaves `x` with an indeterminate value (see lesson 1.6).
- "Object" in this chapter means *a chunk of typed memory*, not "object" in the OOP sense from Chapter 14. Same word, different concept.

## Run
    make 1.03
