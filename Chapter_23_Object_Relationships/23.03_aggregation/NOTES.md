# 23.3 — Aggregation

> learncpp.com: https://www.learncpp.com/cpp-tutorial/aggregation/

## Why it matters
Some "has-a" relationships **don't** want exclusive ownership. A `Department` has `Teacher`s, but `Teacher`s existed before the department was created and will outlive its reorganisation. If you compose them in (by value), you destroy people every time you re-org. Aggregation is the answer: the whole knows about its parts but doesn't *own* them — lifetime stays with whoever originally created them.

## Key points
- Aggregation looks like composition (part-of, has-a) but **flips two rules**:
  - The whole does **not** manage lifetime of the part.
  - The part **can be shared** between multiple wholes (and outlive any of them).
- Implementation: store the part as a **pointer** or **reference** to an externally-managed object. Pass it in at construction; never `new` it inside the aggregate, never `delete` it.
- For *collections* of aggregated objects, raw references don't work (containers can't hold `T&`). Use `std::vector<std::reference_wrapper<T>>` or `std::vector<T*>`.
- Rule of thumb (and the lesson is emphatic about this): **pick the simplest relationship that works**. If composition can model it, use composition — fewer footguns. Aggregate only when shared lifetime is *required*.

## Code in this folder
- `main.cpp` — `Department` aggregates `Teacher`s by pointer. The `Teacher`s outlive the `Department`'s destruction.

## Gotchas
- Aggregation makes you responsible for *not* dangling. If the `Teacher` is destroyed first, the `Department`'s pointer to it is now a landmine. There's no language enforcement; you keep the invariant by design.
- Storing raw `T*` makes ownership ambiguous to readers. If aggregation is what you mean, document it; if exclusive ownership is what you mean, use `std::unique_ptr<T>` (i.e. composition).
- Don't `delete` the pointer in the aggregate's destructor. That's the single bug the relationship is designed to prevent.

## Run
    make 23.03
