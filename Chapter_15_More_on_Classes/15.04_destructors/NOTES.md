# 15.4 — Introduction to destructors

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-destructors/

## Why it matters
Constructors run when an object is born; **destructors** run when it dies. That's where you release whatever the object owned: memory, file handles, locks, sockets. The destructor + constructor pair is the engine of **RAII** ("Resource Acquisition Is Initialization") — the single biggest idea in C++ resource management. Get RAII right and most resource leaks become impossible by construction.

## Key points
- Syntax: `~Foo() { … }`. No parameters, no return type, can't be overloaded.
- Runs **automatically** when a local goes out of scope, a `delete` is called, or a containing object is destroyed.
- Order: members are destroyed in **reverse declaration order** after the destructor body runs.
- If you don't write one, the compiler generates a destructor that destroys each member.
- **Rule of three (C++03) / five (C++11):** if you define one of (destructor, copy ctor, copy assignment) [+ move ctor, move assignment in C++11], you almost always need to define them all. Better still: design so you need **none** of them (rule of zero — use RAII members like `std::vector`, `std::unique_ptr`).
- Destructors **should not throw**. Throwing from a destructor during stack unwinding is undefined behavior in practice.

## Code in this folder
- `main.cpp` — class that owns a heap buffer, with destructor freeing it. Tracing output makes the lifetime visible.

## Gotchas
- Destructor order is reverse of construction. Stack semantics — LIFO.
- A destructor of a polymorphic base class should usually be `virtual` (covered later); without it, `delete basePtr` for a derived object skips the derived destructor → leaks. Not in this chapter, but file the warning.

## Run
    make 15.04
