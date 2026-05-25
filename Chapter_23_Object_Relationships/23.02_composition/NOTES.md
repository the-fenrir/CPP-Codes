# 23.2 — Composition

> learncpp.com: https://www.learncpp.com/cpp-tutorial/composition/

## Why it matters
Composition is the relationship you reach for **by default**. A `Fraction` is made of a numerator and a denominator; a `Creature` is made of a `Point2D` location and a name. The whole *is* the parts, glued together; the parts have no meaningful life outside the whole. This buys you the simplest possible lifetime story: members are born when the object is constructed, die when it's destroyed, in reverse order. No `new`, no `delete`, no aliasing, no surprises.

## Key points
- The four defining properties of composition:
  1. **Part-of** the whole — semantically a piece, not a peer.
  2. The whole **manages the lifetime** of the part. Part is created when the whole is, destroyed with it.
  3. The relationship is **exclusive** — a given part instance belongs to one whole at a time.
  4. The relationship is **unidirectional** — the part doesn't know the whole exists.
- Implementation: just make the part a **non-pointer, non-reference data member** (or a `std::unique_ptr` if you genuinely need dynamic allocation). The language enforces lifetime for free.
- Each class should do one job: either *manage data* (the parts) or *coordinate parts* (the whole). Resist letting `Creature` know how to do `Point2D`'s arithmetic.
- Composition makes classes reusable: `Point2D` doesn't know about `Creature`, so it can be reused inside `Monster`, `Projectile`, `Camera`, etc.

## Code in this folder
- `main.cpp` — `Point2D` and `Creature` composing a `Point2D`. Tracing constructors/destructors makes the lifetime guarantee visible.

## Gotchas
- If you find yourself writing `Creature` code that pokes at `Point2D`'s internals, you've broken the "single responsibility" rule. Move the operation onto `Point2D`.
- Composition does **not** require value-type storage — you can compose via `std::unique_ptr<T>` to get dynamic allocation while keeping all the lifetime semantics. Raw `T*` + manual `new`/`delete` is composition too, but it's the version that leaks under exceptions; don't.

## Run
    make 23.02
