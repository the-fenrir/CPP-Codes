# 21.14 — Overloading operators and function templates

> learncpp.com: https://www.learncpp.com/cpp-tutorial/overloading-operators-and-function-templates/

## Why it matters
Function templates expand for whatever type you instantiate them with. If you wrote `template<typename T> T max(T a, T b) { return (a < b) ? b : a; }`, then calling `max(cents1, cents2)` will *only* compile if `Cents` has an `operator<`. The template is implicitly demanding operators of you. Conversely, if your class has the standard operator set, it slots into the entire generic-programming ecosystem (`std::sort`, `std::set`, `std::map`, range algorithms) for free.

## Key points
- Templates discover operators at instantiation time. A `std::sort` of `std::vector<Cents>` needs `operator<` (pre-C++20) or `operator<=>` (C++20+).
- This is why the spaceship operator in 21.7 is such a big deal: one defaulted line and your class is sortable, searchable, hashable-via-equality.
- "Generic programming-friendly" classes typically provide:
  - `==` and `<=>` (or `<`).
  - Stream `<<` for diagnostics.
  - Copy/move constructors and assignments that do the right thing.
  - A reasonable default constructor (so `std::vector<T>(n)` works).
- You don't need to add an operator overload *inside* the template. The template just calls `a < b`; the lookup happens at instantiation.

## Code in this folder
- `main.cpp` — a `max` template instantiated with `int`, `Cents` (custom `<`), and `std::string`. Same template, three types, one demonstration.

## Gotchas
- A compile error inside a template is reported at the point of instantiation, often pointing at template internals instead of your missing operator. Read the *last* line of the error trail — that's usually the actual missing function.
- Concepts (C++20) let you declare these requirements up front: `template<std::totally_ordered T>` rejects the bad call at the call site with a readable message, instead of dumping template internals.

## Run
    make 21.14
