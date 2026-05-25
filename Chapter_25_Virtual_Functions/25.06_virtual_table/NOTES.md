# 25.6 — The virtual table

> learncpp.com: https://www.learncpp.com/cpp-tutorial/the-virtual-table/

## Why it matters
The vtable is *the* implementation of virtual dispatch in every mainstream C++ compiler. You don't need to know its memory layout to write correct C++, but knowing it exists explains the cost model (one extra pointer per object, one indirection per virtual call) and why some things (constructor calls, `final`, devirtualization) interact with virtual the way they do.

## Key points
- Any class with at least one virtual function (its own or inherited) gets a **vtable** — a per-class array of function pointers, one slot per virtual function in the most-derived signature set.
- Every object of such a class carries a hidden **vptr** as a member (typically the first word). It points at the vtable of the *dynamic* type of that object.
- A virtual call `p->foo()` compiles to: load vptr from `*p`, index into the vtable at `foo`'s fixed slot, call that function pointer. One indirection.
- Constructors set the vptr to the *current class's* vtable before running the body — that's why virtual calls inside a base constructor resolve to the base version, even when the eventual object is a derived. Destructors set it back as they tear down.
- Storage overhead: 1 vptr per object (typically 8 bytes) and 1 vtable per class (not per object). Negligible per-object cost.

## Code in this folder
- `main.cpp` — Prints `sizeof` for a non-polymorphic class and a polymorphic one with the same data, so you can see the vptr. Confirms virtual dispatch picks the right override via `Base*`.

## Gotchas
- The vtable is an implementation detail of the ABI, not the language. Don't write code that inspects it.
- Multiple inheritance (especially with virtual bases — 25.08) makes the layout more complex (thunks, multiple vptrs), but the cost-of-a-call story stays roughly the same.
- "vtable" is the standard name; older books say "vftable" or "vftbl." Same thing.

## Run
    make 25.06
