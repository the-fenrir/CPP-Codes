# 13.12 — Member selection with pointers and references

> learncpp.com: https://www.learncpp.com/cpp-tutorial/member-selection-with-pointers-and-references/

## Why it matters
When you have a pointer or a reference to a struct (not the struct itself), accessing members needs different syntax. References use `.` like the original. Pointers use `->`. That arrow operator is one of the most-used pieces of C++ syntax — get it muscle-memory now.

## Key points
- Reference to struct: `Employee& r = e;` — access members with `r.id`. The reference *is* the object as far as syntax is concerned.
- Pointer to struct: `Employee* p = &e;` — access members with `p->id`. `p->id` is sugar for `(*p).id`.
- Mixing: `c.ceo.name` (object . object . member), `pc->ceo.name` (pointer → object . member), `pc->ceo.salary` works through the arrow only at the first step.
- A pointer to a struct can be `nullptr`; dereferencing it is UB. References can't be null (by construction).
- This is the syntax you'll use throughout Chapter 14 when member functions return refs and through Chapter 15 with `this->`.

## Code in this folder
- `main.cpp` — same struct accessed through a value, a reference, a pointer, and a chained pointer-to-nested-struct.

## Gotchas
- `*p.id` doesn't do what you'd think — `.` binds tighter than `*`, so it parses as `*(p.id)`. Always `(*p).id` or `p->id`.
- A reference can't be re-seated; re-assigning a reference assigns through it. If you want re-seatable, use a pointer.

## Run
    make 13.12
