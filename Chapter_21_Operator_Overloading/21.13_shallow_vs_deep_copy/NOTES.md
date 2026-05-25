# 21.13 — Shallow vs. deep copying

> learncpp.com: https://www.learncpp.com/cpp-tutorial/shallow-vs-deep-copying/

## Why it matters
The compiler-generated copy constructor and `operator=` perform a **shallow copy** — each member is copied with its own copy/assignment semantics. For value types (`int`, `std::string`, `std::vector`) that's exactly right. For classes that own a raw pointer to a resource, shallow copy gives you **two objects pointing at the same memory**, and when both destructors run you get a **double-free**.

## Key points
- Shallow copy = bitwise / memberwise copy. Fine when members own their own copies.
- Deep copy = allocate new storage and copy contents. Required when members are raw pointers/handles.
- Symptom of getting it wrong:
  1. Construct `a`, copy `b = a`.
  2. Both destructors run.
  3. Heap corruption / use-after-free / "free(): double free detected" crash.
- The fix isn't always "write deep-copy ctor + op="; the **better** fix is to *not own raw pointers*:
  - `std::unique_ptr<T>` — non-copyable, moves cleanly. Forces you to think about ownership.
  - `std::shared_ptr<T>` — shared ownership, reference-counted.
  - `std::vector<T>` / `std::string` — already do deep copy.
- If you genuinely need a raw owning pointer: follow the **rule of three / five** rigidly.

## Code in this folder
- `main.cpp` — same `MyString` shape as 21.12, but contrasted against a `BadString` that *only* defines the constructor (no copy ctor / op=). Comments explain what would crash and why.

## Gotchas
- `= delete` is your friend: if a class has no sensible copy semantics, `MyClass(const MyClass&) = delete;` makes the compiler reject copies entirely. Better than a half-broken implicit copy.
- Even with smart pointers, copying a `std::unique_ptr` member is a compile error — which means the default copy ctor for *any* class containing a `unique_ptr` is deleted. That's the point.
- "Shallow copy" sometimes also means "the copy ctor was implicitly defaulted" — those are subtly different ideas. Default ≠ shallow always; for a class containing a `std::vector`, default is a deep copy, because `std::vector` is.

## Run
    make 21.13
