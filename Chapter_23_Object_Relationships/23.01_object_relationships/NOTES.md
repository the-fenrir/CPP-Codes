# 23.1 — Object relationships

> learncpp.com: https://www.learncpp.com/cpp-tutorial/object-relationships/

## Why it matters
Once classes start referring to other classes, you need a vocabulary to describe *how* they refer. "A `Car` has an `Engine`" and "a `Driver` uses a `Car`" sound similar in English but compile to very different code — different ownership, different lifetimes, different rules about who can outlive whom. This lesson names the relationships so the rest of the chapter can teach the rules.

## Key points
- The chapter's relationship taxonomy, weakest coupling to strongest:
  - **Dependency** — *uses-a*, just for one operation. No member stored.
  - **Association** — *uses-a* longer term. A member that points to the other object; lifetimes independent.
  - **Aggregation** — *has-a* part, but the part can outlive the whole and be shared.
  - **Composition** — *part-of*. The part is owned, exclusive, and dies with the whole.
- Plus **member-of** (an object inside a collection) which is just a special case of the same machinery.
- The relationships form a spectrum, not boxes. When in doubt, prefer the *weaker* relationship — easier to reason about, fewer lifetime traps.
- Vocabulary mostly comes from UML; C++ doesn't have keywords for any of them. They're patterns enforced by *how you store the member*, not by the language.

## Code in this folder
- `main.cpp` — four tiny structs, one per relationship, each just enough to make the storage difference visible (member-by-value vs. reference vs. parameter).

## Gotchas
- These labels are guidance, not law. Real codebases sit between the categories all the time. The point isn't to win the naming argument, it's to pick storage that matches the lifetime you actually need.
- "Composition" the relationship is *not* the same thing as "composition over inheritance" the design slogan (though they're related — both prefer containment to is-a).

## Run
    make 23.01
