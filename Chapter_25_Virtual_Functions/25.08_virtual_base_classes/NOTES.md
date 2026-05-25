# 25.8 — Virtual base classes

> learncpp.com: https://www.learncpp.com/cpp-tutorial/virtual-base-classes/

## Why it matters
Multiple inheritance opens up the "diamond problem": if `D` inherits from `B` and `C`, and both `B` and `C` inherit from `A`, then `D` ends up with **two** copies of `A` — one via `B`, one via `C`. Ambiguous access, duplicated state, generally not what you want. **Virtual inheritance** says "share `A`": there's exactly one `A` sub-object regardless of how many paths reach it.

## Key points
- Syntax: in `B` and `C`, write `class B : virtual public A` and `class C : virtual public A`. Now `D : public B, public C` has one shared `A`.
- The **most-derived class** (`D`) is responsible for constructing the virtual base directly. `B`'s and `C`'s `A`-constructor mentions in their initializer lists are ignored when they're sub-objects of `D`.
- This adds a small amount of overhead (extra indirection to find the shared sub-object) and a fair bit of complexity. Avoid multiple inheritance from non-interface classes when you can; reach for virtual inheritance only when you actually have a diamond you can't refactor away.
- Pure interfaces (25.07) avoid the diamond problem in practice because there's no state to duplicate — duplicating two empty bases is harmless.

## Code in this folder
- `main.cpp` — A classic diamond: `PoweredDevice` shared by `Scanner` and `Printer`, joined in `Copier`. Without `virtual`, you'd have two `PoweredDevice` sub-objects and ambiguous access; with `virtual` you have one, constructed by `Copier`.

## Gotchas
- The most-derived class must initialize the virtual base. That includes every leaf in the hierarchy — easy to forget when you add a new derived class later.
- Virtual base constructors run **before** non-virtual base constructors, regardless of declaration order in the initializer list.
- Order of base initialization in the most-derived class: virtual bases first (in declaration order across the hierarchy), then non-virtual bases (in declaration order), then members.
- This is one of the dustier corners of C++. Most production codebases avoid it entirely by preferring composition or interface-only multiple inheritance.

## Run
    make 25.08
