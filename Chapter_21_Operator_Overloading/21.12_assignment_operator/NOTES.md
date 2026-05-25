# 21.12 — Overloading the copy assignment operator

> learncpp.com: https://www.learncpp.com/cpp-tutorial/overloading-the-assignment-operator/

## Why it matters
`a = b;` between **already-constructed** objects calls `operator=`. The compiler generates a default member-wise version automatically; for classes owning raw resources (heap memory, file handles) that default is wrong and you must write your own. Distinguish from the copy *constructor* (14.14), which runs when a brand-new object is being initialised from an existing one.

## Key points
- Signature: `T& T::operator=(const T& rhs);`  — must be a member, returns `*this` by ref to enable chaining (`a = b = c;`).
- **Self-assignment check** before doing anything that destroys current state:
  ```cpp
  if (this == &rhs) return *this;
  ```
  Skipping it on a class that frees and re-copies a resource turns `a = a;` into a use-after-free.
- The **copy-and-swap idiom** sidesteps the self-assignment problem and gives strong exception safety:
  ```cpp
  T& operator=(T rhs) { swap(*this, rhs); return *this; }   // by value!
  ```
- Rule of three: if you write any of {destructor, copy ctor, copy assignment}, you almost certainly need all three. Rule of five with move ctor/move assign added.
- Or — the modern answer — **don't**. Use `std::unique_ptr`, `std::vector`, etc. and let `= default` do everything.

## Code in this folder
- `main.cpp` — a `MyString` that owns a `char*`, with copy ctor, copy assignment (with self-assignment guard), and destructor. Comments mark the foot-guns.

## Gotchas
- Forgetting `return *this;` makes chained assignment fail to compile in unintuitive ways.
- Self-assignment is rare in real code but trivial to trigger through references / aliasing. The check is cheap; do it.
- If you write copy assignment but skip the copy *ctor*, the compiler generates a member-wise copy ctor that shallow-copies your pointer. You will get a double-free.

## Run
    make 21.12
