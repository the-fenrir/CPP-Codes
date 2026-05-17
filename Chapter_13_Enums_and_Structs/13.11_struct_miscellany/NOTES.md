# 13.11 — Struct miscellany

> learncpp.com: https://www.learncpp.com/cpp-tutorial/struct-miscellany/

## Why it matters
A grab-bag chapter that cleans up edges: structs that contain structs, structs that contain arrays, anonymous structs, why size is not always the sum of member sizes (padding/alignment). You don't need to memorize the rules — you need to know that they exist so you stop being surprised.

## Key points
- **Structs containing structs** are first-class — just use aggregate init recursively: `Company c{ "Acme", { 99, "Eve", 250000.0 } };`.
- **Structs containing arrays / `std::array`** also aggregate-init normally.
- **`sizeof(S)` is not always `sum of sizeof(members)`** — the compiler inserts **padding** so each member is aligned. Re-ordering members can shrink the struct.
- A struct's alignment is the strictest alignment of any member.
- **Forward declarations** of a struct (`struct Foo;`) declare the type as *incomplete* — usable by pointer or reference, not by value. Useful in headers to break cyclic includes.

## Code in this folder
- `main.cpp` — nested struct init, struct with a `std::array`, and a `sizeof` comparison of two struct layouts that differ only in member order.

## Gotchas
- Don't `memcpy` two structs that differ in padding bytes and expect a meaningful comparison — the padding is unspecified.
- Forward-declared structs can't be members by value (the compiler doesn't know how big they are). Pointers/references are fine.

## Run
    make 13.11
