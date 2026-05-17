# 12.7 — Introduction to pointers

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-pointers/

## Why it matters
A pointer is an object whose value is a memory address. Unlike a reference, a pointer is **itself an object**: it has its own address, can be reassigned, and can be null. Pointers are the foundation of dynamic memory, polymorphism, optional/out parameters, and C-interop.

## Key points
- **Address-of operator** `&x` — yields the address of `x` (an rvalue of type `T*`).
- **Dereference operator** `*p` — yields the object `p` points at (an lvalue of type `T`).
- Declaration: `T* p { &x };` — `p` is a pointer to `T`, initialized to `x`'s address.
- A pointer has its own storage (`sizeof(T*)` is typically 8 on 64-bit). A reference (mostly) does not.
- Pointers are **rebindable**: `p = &y;` makes `p` point at `y`. Compare with `ref = y;` which assigns into `*ref` and never rebinds.
- An uninitialized pointer (`int* p;` at block scope) contains garbage — dereferencing it is undefined behavior. **Always initialize**, at minimum to `nullptr` (next lesson).
- A pointer is `true` in a boolean context iff non-null; idiomatic null check is `if (p)`.

## Code in this folder
- `main.cpp` — declare, take address, dereference, rebind. Print addresses to make the indirection concrete.

## Gotchas
- `int* a, b;` declares **one** `int*` and **one** `int`. The `*` binds to the variable, not the type. Either declare one per line, or learn to read it carefully.
- Taking `&` of an rvalue is illegal: `&5` is an error.
- Dereferencing a dangling or null pointer is UB, not a guaranteed crash. The program may appear to "work" while corrupting memory.
- A pointer and a reference are different: `&ref` returns the address of the *referenced object*, but `&p` returns the address of the *pointer itself*.

## Run
    make 12.07
