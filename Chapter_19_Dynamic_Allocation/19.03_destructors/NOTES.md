# 19.3 — Destructors

> learncpp.com: https://www.learncpp.com/cpp-tutorial/destructors/

## Why it matters
A constructor's job is to take an object from "raw memory" to "valid object." A destructor's job is the reverse — and crucially, it runs *automatically* at the end of the object's lifetime. That's the whole basis for RAII: any resource you acquire in a constructor and release in the matching destructor is guaranteed to be released, even if exceptions are thrown or early returns happen. This is what makes `std::vector`, `std::unique_ptr`, `std::lock_guard`, and `std::fstream` actually work.

## Key points
- Syntax: `~ClassName()`. No parameters, no return type, exactly one per class.
- Runs automatically when:
  - a stack object falls out of scope,
  - a heap object is `delete`d (or `delete[]`d),
  - a global/`static` is destroyed at program exit (after `main` returns).
- Destruction order is **reverse** of construction order (LIFO). Members are destroyed after the enclosing object's destructor body, in reverse declaration order.
- **RAII** ("Resource Acquisition Is Initialization"): wrap each resource in a small class whose destructor releases it. Now leaks are a *type-system* impossibility, not a discipline problem.
- `std::exit()` and `std::_Exit()` skip destructors on stack/static objects — don't rely on RAII cleanup if you forcibly terminate.

## Code in this folder
- `main.cpp` — an `IntArray` class that owns a `new[]` array. Constructor allocates, destructor `delete[]`s. Drives it on the stack and on the heap so you can see both destruction paths fire. Prints traces to make the order visible.

## Gotchas
- Forget the destructor on a class that owns a `new`/`new[]` resource → guaranteed leak the moment one of those objects is destroyed.
- Once a class has an owning destructor, the compiler-generated copy constructor and copy assignment are wrong (they'll double-`delete`). This is the **Rule of Three**: if you write one of {destructor, copy ctor, copy assign}, you almost certainly need all three. Chapter 22 makes this precise; for now, the example below either disables copying or uses `std::vector` instead.
- Never call a destructor explicitly (`obj.~T()`). It runs on its own; explicit calls are for placement-new gurus only.
- Modern alternative: don't write a destructor at all — store `std::vector<int>` instead of `int*`. The vector's destructor does the right thing for free.

## Run
    make 19.03
