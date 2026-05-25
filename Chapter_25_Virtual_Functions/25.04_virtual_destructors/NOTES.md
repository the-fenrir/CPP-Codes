# 25.4 — Virtual destructors, virtual assignment, and overriding virtualization

> learncpp.com: https://www.learncpp.com/cpp-tutorial/virtual-destructors-virtual-assignment-and-overriding-virtualization/

## Why it matters
If you ever `delete` a derived object through a `Base*`, and `~Base` isn't `virtual`, **only `~Base` runs** — `~Derived` is skipped, and any derived-owned resources leak. This is the single most common UB in polymorphic code. Rule: any class meant to be used as a polymorphic base needs a virtual destructor.

## Key points
- Polymorphic base → `virtual ~Base() = default;`. Cost is essentially the same as any other virtual function — one vtable slot.
- The rule is conservative: even if *you* never plan to delete through a base pointer, you can't stop others from doing it. Defaulting to virtual destructors on bases is the safe default.
- Virtual assignment is rarely useful. `operator=` returning a `Base&` doesn't compose well with derived assignment (signature changes break overriding, slicing kicks in). Most production code leaves assignment non-virtual and disables it on polymorphic bases (or makes the base abstract).
- **Overriding virtualization**: explicit scope-qualified calls (`base.Base::foo()`) bypass virtual dispatch. Useful inside a derived override that wants to chain to the base implementation: `Derived::foo() { Base::foo(); /* ...extra... */ }`.

## Code in this folder
- `main.cpp` — Two hierarchies side by side: one with non-virtual `~Base` (leaks `~Derived` work — visible via a tracer), one with `virtual ~Base` (both destructors run). Also shows `Derived::foo()` calling `Base::foo()` explicitly.

## Gotchas
- A virtual destructor in the base does *not* require the keyword in the derived — once virtual, always virtual. But `~Derived() override` is still good style.
- If you give a base a virtual destructor, also think about copy/move semantics — see the Rule of 3/5 (15.04). Often you want the base non-copyable to prevent slicing.
- `delete static_cast<Base*>(p)` with non-virtual `~Base` is undefined behavior, not just a leak — compilers may optimize on the assumption it won't happen.

## Run
    make 25.04
