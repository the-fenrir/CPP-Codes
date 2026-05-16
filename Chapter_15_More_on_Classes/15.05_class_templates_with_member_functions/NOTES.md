# 15.5 — Class templates with member functions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/class-templates-with-member-functions/

## Why it matters
A class template is the same idea as a function template: write once, work for many types. `std::vector<int>` and `std::vector<std::string>` come from the same `vector<T>` template. Once you can write `Pair<T, U>`, an enormous swath of the standard library stops feeling magical and starts feeling buildable.

## Key points
- Declare with `template <typename T> class Foo { … };`. `T` is a parameter — anything legal in that role works.
- Each `Foo<X>` is a **distinct type** (different instantiation): `Foo<int>` and `Foo<double>` share zero code at runtime.
- Member functions defined **outside** the class need the template header repeated: `template <typename T> void Foo<T>::bar() { … }`.
- Templates are **instantiated per use** — bodies must be visible to the compiler at the call site. That's why class templates live entirely in headers (no header/source split).
- C++17 **class template argument deduction** (CTAD): `Pair p{ 1, 2.5 };` works without `<int, double>`.
- Multiple type parameters and non-type template parameters (NTTPs) — `Array<int, 16>` — are both fine.

## Code in this folder
- `main.cpp` — `Pair<T, U>` with member functions defined inside and outside the class body; CTAD example.

## Gotchas
- "I split my template class into .h/.cpp and now the linker can't find the methods" — you *can't* do that for templates without extra dances (explicit instantiation). Put it all in the header.
- Each instantiation generates separate code → binary bloat if you over-templatize trivial types.
- Watch error messages for `Foo<int>` vs. `Foo<long>` mismatches — they're different types even when they look interconvertible.

## Run
    make 15.05
