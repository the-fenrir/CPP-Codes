# 12.9 — Pointers and const

> learncpp.com: https://www.learncpp.com/cpp-tutorial/pointers-and-const/

## Why it matters
There are four `const`-related pointer combinations, and they mean different things. Confusing "pointer to const" with "const pointer" is one of the most common C++ errors — and it shows up constantly in API design.

## Key points
- **Pointer to non-const** (`int*`) — can modify the pointee, can repoint.
- **Pointer to const** (`const int*` or `int const*`) — **cannot** modify the pointee through `*p`, **can** repoint.
- **Const pointer to non-const** (`int* const`) — **can** modify the pointee, **cannot** repoint.
- **Const pointer to const** (`const int* const`) — neither.
- **Read right-to-left.** `int const * const` = "const pointer to const int". The `const` left of `*` qualifies the pointee; the `const` right of `*` qualifies the pointer.
- A `const T*` may point at a non-const object — you simply can't modify the object *through this pointer*.
- A non-const pointer cannot point at a const object (it'd silently strip `const`).

## Code in this folder
- `main.cpp` — all four combinations, with commented-out illegal assignments.

## Gotchas
- `const int*` vs `int* const` — first is much more common, second appears mostly in class member pointers and embedded code.
- `const int& r = x;` vs. `const int* p = &x;` — same constness rules on the pointee; reference syntax is just an alias for the pointer pattern in most APIs.
- Once you understand "the `const` left of `*` is the pointee, right of `*` is the pointer," `const int* const* const` stops being intimidating: const pointer to const pointer to const int.
- Discarding `const` via `const_cast` is a smell and usually UB if you then modify a *truly const* object.

## Run
    make 12.09
