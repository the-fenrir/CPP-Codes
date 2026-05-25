# 22.1 — Introduction to smart pointers and move semantics

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/

## Why it matters
Every raw `new` creates an ownership question: *who* calls `delete`, and *when*? Get it wrong on any path — early return, thrown exception, second pointer to the same object — and you leak or double-free. The fix is RAII: wrap the pointer in a class whose destructor frees it. That's a smart pointer. But a naive smart pointer that *copies* its raw pointer in its copy constructor causes a double-delete, so copy needs to be replaced with **move**: transfer ownership, leave the source empty.

## Key points
- **RAII** — resource acquired in the constructor, released in the destructor. Cleanup runs automatically at scope exit, including during exception unwinding.
- A raw-pointer leak example: `new` then `return` or `throw` before `delete` → leak. RAII fixes it for free.
- A smart pointer is a small class that owns one heap object. Make the destructor `delete` what it points at.
- Copying a smart pointer that just memberwise-copies the raw pointer ⇒ two owners ⇒ double-delete on scope exit.
- **Move semantics** sidesteps that: copy ctor/assign are disabled (or made to transfer), and a *move* ctor takes the pointer out of the source and nulls it. Source is left valid-but-empty.
- The standard library already ships these: `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr` (lessons 22.05–22.07). Don't roll your own in production.

## Code in this folder
- `main.cpp` — three escalating versions of a `Resource` owner:
  1. raw pointer, leaks on early return,
  2. hand-rolled smart pointer that double-frees on copy,
  3. same wrapper with copy deleted and a move ctor — works.

## Gotchas
- "RAII" doesn't require dynamic allocation; it's a pattern. `std::lock_guard`, `std::fstream`, `std::vector` all use it. Smart pointers are just RAII applied to `new`.
- After a move, the source object is still alive — its destructor will still run. Make sure that's harmless (i.e. the pointer is null).
- Don't write your own smart pointer for real code. The standard ones handle alignment, arrays, custom deleters, exception safety, and aliasing constructors you haven't thought of.

## Run
    make 22.01
