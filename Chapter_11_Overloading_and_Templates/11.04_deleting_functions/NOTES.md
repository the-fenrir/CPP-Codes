# 11.4 — Deleting functions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/deleting-functions/

## Why it matters
Sometimes you want a function to be *visible* to overload resolution but *uncallable* for certain argument types — to forbid a silent conversion that would otherwise pick a worse overload. `= delete` is the idiom: the function still exists at the overload-set level, but selecting it is a compile error. Common use: stop `print(char)` from quietly promoting through `print(int)`.

## Key points
- `void f(SomeType) = delete;` declares-and-deletes. Resolving to it is an error with a clear message.
- Most useful as a **deleted overload** — block a specific conversion path without removing the others.
- Different from "not declared": an undeclared `f(char)` falls back to `f(int)` via promotion silently; a deleted `f(char) = delete;` makes that call an error.
- Also used to suppress compiler-generated members (copy ctor, copy-assign) — covered later in Chapter 14/22.
- Can delete **all** overloads except chosen ones with a deleted template: `template <typename T> void f(T) = delete;`.

## Code in this folder
- `main.cpp` — `printInt(int)` plus `printInt(char) = delete;` to forbid char-promotion. Calling `printInt('a')` shows the error in a commented-out section.

## Gotchas
- Deleting only `char` doesn't stop `bool` or `short` — extend the deletion as needed, or use the template-delete trick.
- A deleted function is still part of the overload set; it can still be the **best match** — that's the point.

## Run
    make 11.04
