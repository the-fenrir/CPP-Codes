# 13.7 — Introduction to structs, members, and member selection

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-structs-members-and-member-selection/

## Why it matters
Every program eventually has bundles of related values: a point has *x* and *y*, an employee has a name, id, and salary. Passing them as separate function parameters scales horribly. A `struct` lets you give that bundle a name and a type — once defined, the compiler tracks which fields belong together.

## Key points
- Definition: `struct Employee { int id; double salary; };`. Each `id`/`salary` is a **data member** (a.k.a. field).
- Instantiation: `Employee e;` (members default-init — for built-ins, that means *uninitialized*; see 13.9).
- **Member access** uses the dot operator: `e.id`, `e.salary`.
- A `struct` is a *type*. The members exist *per object*: `e1.id` and `e2.id` are independent.
- Structs can hold structs (composition). Member access chains: `company.ceo.salary`.

## Code in this folder
- `main.cpp` — defines an `Employee` and a nested `Company`, accesses members with `.`.

## Gotchas
- Defining a struct doesn't allocate anything. Only declaring a variable of that type does.
- Forgetting the trailing `;` after the closing `}` is the classic newcomer error.
- Default-initializing a built-in member leaves it indeterminate — reading it is undefined behaviour. 13.8/13.9 show how to fix this.

## Run
    make 13.07
