# Chapter 25 — Virtual Functions

Chapter 25 is the chapter where inheritance becomes useful. Chapter 24 set up "Derived is-a Base"; this chapter is how a `Base*` actually *behaves like* the derived object it points at — virtual dispatch, vtables, pure-virtual interfaces, and the gotchas that come with mixing the two (slicing, non-virtual destructors, the diamond).

## Lessons

| # | Lesson |
|---|---|
| 25.01 | [Pointers and references to the base class of derived objects](25.01_pointers_refs_to_base/NOTES.md) |
| 25.02 | [Virtual functions and polymorphism](25.02_virtual_functions/NOTES.md) |
| 25.03 | [The `override` and `final` specifiers, and covariant return types](25.03_override_final_covariant/NOTES.md) |
| 25.04 | [Virtual destructors, virtual assignment, and overriding virtualization](25.04_virtual_destructors/NOTES.md) |
| 25.05 | [Early binding and late binding](25.05_early_late_binding/NOTES.md) |
| 25.06 | [The virtual table](25.06_virtual_table/NOTES.md) |
| 25.07 | [Pure virtual functions, abstract base classes, and interface classes](25.07_pure_virtual_abstract_interfaces/NOTES.md) |
| 25.08 | [Virtual base classes](25.08_virtual_base_classes/NOTES.md) |
| 25.09 | [Object slicing](25.09_object_slicing/NOTES.md) |
| 25.10 | [Dynamic casting](25.10_dynamic_casting/NOTES.md) |
| 25.11 | [Printing inherited classes using `operator<<`](25.11_printing_inherited_with_op_lshift/NOTES.md) |
| 25.x | [Summary & quiz](25.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear, with a few natural clusters:

- **25.01 → 25.02 → 25.03** — the mechanical core. 25.01 shows that a `Base&` to a `Derived` calls *Base* members by default; 25.02 fixes that with `virtual`; 25.03 (`override`/`final`) is how you stop fooling yourself when you do it.
- **25.04** — the destructor *must* be virtual if you ever delete through a base pointer. Short lesson, save-your-bacon importance.
- **25.05 → 25.06** — early vs. late binding and the vtable. This is the "how does it work under the hood" pair. Don't memorize the vtable layout; understand *why* virtual costs a pointer indirection.
- **25.07** — pure virtual functions and interfaces. The OOP design payoff of everything above it.
- **25.08** — the diamond / virtual inheritance. Rare in real code; learn it once, recognize it forever.
- **25.09 → 25.10** — slicing is the #1 polymorphism bug; `dynamic_cast` is the safe-but-slow downcast. Read them as a pair: slicing is what happens when you store derived *by value*, `dynamic_cast` is what you reach for when you stored it *by pointer* and now need to recover the derived type.
- **25.11** — the `operator<<` trick (free function forwards to a virtual `print`). Tiny but very satisfying once 25.02 and 25.07 click.
