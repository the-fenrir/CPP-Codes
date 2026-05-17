# 1.4 — Variable assignment and initialization

> learncpp.com: https://www.learncpp.com/cpp-tutorial/variable-assignment-and-initialization/

## Why it matters
Every variable starts life with *some* value. Whether that value is what you intended depends entirely on **how** you brought the variable into existence. Picking one initialization style and using it consistently eliminates a huge class of bugs.

## Key points
- **Assignment** (`x = 5;`) replaces the value of an already-existing variable. Can happen any number of times.
- **Initialization** sets the value as the variable is created. Happens once.
- C++ supports several initialization forms:
  - **Copy-init**: `int x = 5;` — old C-style.
  - **Direct-init**: `int x(5);` — looks like a function call.
  - **Direct-list-init / brace-init**: `int x{ 5 };` — **preferred**.
  - **Value-init**: `int x{};` — zero-initializes (`x == 0`).
- Brace-init disallows **narrowing conversions**: `int x{ 4.5 };` is a compile error, `int x = 4.5;` silently truncates.

## Code in this folder
- `main.cpp` — shows each initialization form and which conversions each one allows or rejects.

## Gotchas
- `int x();` is **not** value-initialization of an `int` — it's a declaration of a function named `x` that returns `int` (the "most vexing parse"). Use `int x{};` instead.
- Brace-init is the safest because it catches the case where you accidentally lose precision. Default to it.

## Run
    make 1.04
