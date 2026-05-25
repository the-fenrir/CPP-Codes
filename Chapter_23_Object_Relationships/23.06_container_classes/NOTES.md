# 23.6 — Container classes

> learncpp.com: https://www.learncpp.com/cpp-tutorial/container-classes/

## Why it matters
Almost every program holds *collections* of things. The standard library hands you `std::vector`, `std::array`, `std::map`, etc — but those types don't fall out of nowhere. Building one yourself, even badly, is how you learn what they had to solve: ownership of the underlying storage, growing, copying, indexing, cleanup. Once you've written `IntArray`, `std::vector` stops being magic.

## Key points
- A **container class** holds zero or more instances of some element type and provides operations on the collection.
- Two flavours:
  - **Value containers** — store the elements *by value*, own them, destroy them with the container. This is composition applied to a collection.
  - **Reference containers** — store pointers/references to externally-owned elements. Aggregation applied to a collection.
- Standard "vocabulary" of container operations: construct (empty / sized / from a list), destroy, copy, assign, insert, remove, access (`operator[]`), size, clear, optionally sort/find.
- Implementation building blocks for a value container that owns dynamic storage: a `T*` member, a size, a destructor that `delete[]`s, a copy constructor and assignment operator that **deep-copy**, plus `operator[]` and helpers (`resize`, `reallocate`, `insertBefore`, `remove`).
- "Rule of zero" wins in production: prefer composing `std::vector<T>` inside your class and let it handle all of the above. Roll your own only as an exercise or for a hard reason.

## Code in this folder
- `main.cpp` — `IntArray`: dynamic int container with size, deep-copying copy ctor/assignment, `operator[]`, `resize`, `reallocate`, `insertBefore`, `remove`, `erase`. The shape mirrors a stripped-down `std::vector<int>`.

## Gotchas
- The destructor and copy ops are not optional. A container that owns `new[]` storage without a deep-copying copy constructor will double-free the moment it's passed by value. **Rule of three** in action.
- `reallocate()` is "fast but destructive" — it throws away the old contents. `resize()` preserves them. Don't pick the wrong one to save typing.
- `operator[]` doesn't do bounds checking; add `assert` (or throw from an `at()`) if you want safety. `std::vector` made the same trade-off — `[]` fast, `at()` checked.

## Run
    make 23.06
