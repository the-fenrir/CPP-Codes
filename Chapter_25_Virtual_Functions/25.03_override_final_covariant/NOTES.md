# 25.3 — The `override` and `final` specifiers, and covariant return types

> learncpp.com: https://www.learncpp.com/cpp-tutorial/the-override-and-final-specifiers-and-covariant-return-types/

## Why it matters
Override silently failing is the #1 polymorphism bug. `override` makes the compiler check that your derived function actually overrides something; `final` lets you stop further overriding/inheritance. Both cost nothing at runtime and pay for themselves the first time they catch a typo.

## Key points
- `override` (on the derived function) tells the compiler "I expect to be overriding a virtual function with this exact signature." If the signature doesn't match a virtual base member, the program fails to compile.
- `final` on a virtual function stops anyone further down from overriding it. `final` on a class stops anyone from inheriting from it at all.
- Use `override` on every override you write. Repeating `virtual` on overrides is redundant; `override` is the right keyword.
- **Covariant return types**: a `virtual Base* clone()` can be overridden by `Derived* clone()` — return type may narrow if both returns are pointer/reference to classes in the same hierarchy. Caller through `Base*` still sees `Base*`; direct caller on `Derived*` sees `Derived*` with no cast needed.
- Override + final go after the parameter list / cv-qualifiers: `void f() const override final;`.

## Code in this folder
- `main.cpp` — Demonstrates `override` catching a typo (commented-out failing case), `final` blocking further derivation, and a covariant `clone()`.

## Gotchas
- A common silent-fail: `virtual void f();` in base, `void f() const;` in derived. Without `override`, this compiles as an overload, and you get the base version through `Base&`. With `override`, the compiler stops you.
- `final` on a leaf class is mostly a hint to the compiler/reader; on a virtual method it's a real promise — devirtualization can drop the vtable indirection.
- Covariance only applies to **pointers/references** to types in the same hierarchy. Not to value returns. Not to other type relationships.

## Run
    make 25.03
