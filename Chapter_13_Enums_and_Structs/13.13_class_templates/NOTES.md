# 13.13 — Class templates

> learncpp.com: https://www.learncpp.com/cpp-tutorial/class-templates/

## Why it matters
A `Pair` of two `int`s and a `Pair` of two `double`s are the same shape but different types. Writing two structs is duplication; writing one *class template* and letting the compiler stamp out per-type versions is the right answer. Same idea as a function template, but for the type itself.

## Key points
- Syntax: `template <typename T> struct Pair { T first; T second; };`. `Pair<int>`, `Pair<double>`, `Pair<std::string>` are distinct types.
- Multiple parameters: `template <typename T, typename U> struct Pair { T first; U second; };`.
- A class template isn't a type. `Pair<int>` is. You can't have a member of type `Pair` — you need `Pair<something>`.
- Member functions of class templates are themselves implicitly function templates over the same parameters. Their bodies are typically defined inside the class so the definition is visible at every instantiation site.
- Definition placement: class templates live in **headers** — the compiler must see the template definition wherever it's instantiated.

## Code in this folder
- `main.cpp` — a `Pair<T>` and a `Pair<T, U>` (illustrating partial-template-name reuse via overloads of a `print` function template).

## Gotchas
- Compile errors inside class templates often point deep into the instantiation chain. Read from the bottom up to find your callsite.
- Two `Pair<int>`s are the same type; `Pair<int>` and `Pair<long>` are not — no implicit conversion between them.

## Run
    make 13.13
