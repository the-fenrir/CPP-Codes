# 24.4 — Constructors and initialization of derived classes

> learncpp.com: https://www.learncpp.com/cpp-tutorial/constructors-and-initialization-of-derived-classes/

## Why it matters
A derived class can't initialize its base subobject by assigning to base members from its own constructor body — by that point the base has already been default-constructed. The only correct hook is the **member initializer list**, where you name the base type as if it were a member and pass it the arguments it needs.

## Key points
- Form: `Derived(args) : Base{ baseArgs }, m_x{ ... } {}`. The base "call" must be the first entry; member-init entries follow.
- If you don't name the base, the compiler calls the **base's default constructor**. If the base has no usable default, that's a compile error — force the issue by listing the base explicitly.
- The derived constructor's job is: forward what the base needs, then initialize the new derived-only members.
- Inheritance does **not** inherit constructors by default. To reuse base constructors verbatim, write `using Base::Base;` (out of scope here, but worth knowing it exists).
- Same rule applies to copy/move: a derived copy ctor that doesn't list `Base{ other }` will default-construct the base, silently dropping base state.

## Code in this folder
- `main.cpp` — `Base` with a 1-arg constructor and `Derived` that forwards to it; shows the initializer-list syntax and demonstrates that the base part receives its argument.

## Gotchas
- Assigning to inherited members in the constructor *body* works but is wrong: the base subobject was already default-constructed and then immediately overwritten. Use the initializer list.
- The base type can appear in the initializer list **only once**, and it must come before any member initializers. The compiler will reorder member-init entries to declaration order anyway, but the base goes first.

## Run
    make 24.04
