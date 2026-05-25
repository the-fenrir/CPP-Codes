# Chapter 23 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-23-summary-and-quiz/

## One-page recap

### The four relationships (23.1–23.5)

| Name | English | Lifetime | Sharing | Direction | Stored as |
|---|---|---|---|---|---|
| **Composition** | part-of | whole owns part; dies with it | exclusive | one-way | value member (or `unique_ptr`) |
| **Aggregation** | has-a | independent | shared | one-way | pointer / reference |
| **Association** | uses-a (ongoing) | independent | shared | one- or two-way | pointer / reference / id |
| **Dependency** | uses-a (one shot) | none | n/a | one-way | parameter / local / global |

Rule of thumb: **pick the simplest relationship that works.** Composition first, dependency next, association and aggregation when independent lifetime is genuinely required. The complexity of a relationship is proportional to the lifetime invariants you now have to maintain by hand.

### Container classes (23.6)
- A class that holds zero-or-more elements and provides operations on the collection.
- *Value containers* own and destroy their elements (composition over a collection); *reference containers* don't (aggregation over a collection).
- A correctly-written value container that uses `new[]` storage needs: destructor (frees), deep-copy constructor, deep-copy assignment (rule of three).
- Operations the chapter calls out: construct (empty / sized / list), destroy, copy, assign, insert, remove, access, size, clear, optionally sort.
- In real code: just use `std::vector<T>`. The exercise teaches what `std::vector` had to handle.

### `std::initializer_list` (23.7)
- `Foo(std::initializer_list<T>)` enables `Foo f{ a, b, c };` for your class.
- Pair it with `operator=(std::initializer_list<T>)` so brace-assign works too.
- Trap: once a list constructor exists, **brace init prefers it** over other constructors. `IntArray a{ 5 };` becomes "list of one element 5", not "size-5 array". Use parens (`IntArray a(5);`) for the non-list constructor.

## Quiz

The chapter's quiz is purely classification. For each scenario, label the relationship as composition, aggregation, association, or dependency, and justify briefly.

### Q1 — Classify each relationship

**1a.** An `Animal` class that contains an animal type (enum) and a name (`std::string`).

**1b.** A text editor class with a `save()` function that takes a `File` object as an argument. The `save()` function writes the contents of the editor to disk.

**1c.** An `Adventurer` class that can carry various kinds of `Item`s — swords, wands, potions, spellbooks. These items can be dropped and picked up by other adventurers.

**1d.** The `Player` prays at a `Shrine` (to receive a new power).

**1e.** A `Computer` class that contains a `CPU` class. The `CPU` can be removed from the `Computer` and tested on its own.

**1f.** A blacksmith has a specific anvil that he uses to do his work.

### Q2 — Which relationship is preferred by default?

If you can design a class using **(pick one: composition, aggregation, association, or dependency)**, then you should.

## Answers

### Q1

**1a — Composition.** The type (enum) and the name (string) are *part-of* the `Animal`; they're born and destroyed with it, exclusive to that animal, and have no meaning on their own. Stored as value members. (`std::string` *internally* owns a heap buffer, but from `Animal`'s viewpoint it's still composed-in by value.)

**1b — Dependency.** The editor uses a `File` for one operation (`save()`) and doesn't otherwise track it. No member, no ongoing relationship — the `File` is a parameter that's used and forgotten.

**1c — Aggregation.** `Adventurer` has `Item`s (has-a, part-of the inventory in a loose sense), but items can be dropped and picked up by *other* adventurers — so they're shared, lifetimes are independent of any particular adventurer, and no adventurer destroys them. Stored as pointers/references.

**1d — Dependency.** Praying-at-a-Shrine is one short interaction. Player doesn't keep a member pointing to the shrine afterwards; the shrine doesn't track the player. Pass the shrine in for that single operation and forget it.

**1e — Aggregation.** A CPU is part of a computer (has-a), but it can be physically removed and tested on its own — so it's not destroyed with the computer, can move between computers, and the computer doesn't manage its lifetime. Same logic as Teacher/Department.

**1f — Association.** The blacksmith has a *specific* anvil (ongoing, long-term link, peer-to-peer — neither is part of the other, neither owns the other). Differs from dependency because the link is persistent: the blacksmith *uses this anvil over and over*, so it makes sense to store a reference to it.

### Q2

**Composition.** Composition gives you the strongest lifetime guarantees, the simplest implementation (no pointers to manage), no aliasing, no sharing — and therefore the fewest ways to be wrong. Reach for weaker relationships only when shared / independent lifetimes are *required* by the design.

## Run

    make 23.x

`quiz_solutions.cpp` contains tiny `static_assert`-style examples for each classification — each scenario implemented in the storage shape that matches the correct answer, with comments explaining why that storage choice expresses that relationship.
