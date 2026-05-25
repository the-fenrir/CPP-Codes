# 25.9 — Object slicing

> learncpp.com: https://www.learncpp.com/cpp-tutorial/object-slicing/

## Why it matters
Polymorphism in C++ works through pointers and references. Try to do it through *values* and you get **slicing**: the derived parts of the object are sliced off and only the base sub-object survives the copy. The vptr in the copy points at `Base`'s vtable, virtual calls dispatch to `Base`, and your "polymorphic container" silently turns into a base-only zoo.

## Key points
- Assignment/copy-by-value to a `Base` slices: `Base b = derived;` constructs a `Base` from the base sub-object of `derived` and discards the rest.
- Pass-by-value `void f(Base b)` slices on every call. Use `void f(const Base& b)` instead.
- `std::vector<Base>` slices on `push_back(derived)` for the same reason. For polymorphic containers, store **pointers** (raw if lifetime is managed elsewhere, otherwise `std::unique_ptr<Base>`).
- Slicing through a pointer to a stack-allocated derived followed by assignment is a particularly nasty case: the base of `d` gets overwritten by some other base, derived state is now inconsistent with its (sliced) base. Don't do partial assignments across the hierarchy.

## Code in this folder
- `main.cpp` — Three slicing scenarios: pass-by-value, copy into a `Base`, and `std::vector<Base>` of supposed-derived. Each prints `Base::name()` even though the original was a `Derived`. Then the same examples done correctly with references / `vector<Base*>`.

## Gotchas
- The compiler will happily slice. There's no warning — copying `Derived` into a `Base` is a well-formed operation by design (you're using the inherited base constructor).
- Some teams forbid copy/copy-assign on polymorphic bases entirely (`Base(const Base&) = delete;`) precisely to make accidental slicing a compile error. Worth considering.
- "Slicing" is a runtime concept, but the way to *prevent* it is at design time: keep polymorphic types non-copyable, hold them by pointer.

## Run
    make 25.09
