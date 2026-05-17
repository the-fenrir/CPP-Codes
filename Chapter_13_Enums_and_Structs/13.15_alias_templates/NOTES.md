# 13.15 — Alias templates

> learncpp.com: https://www.learncpp.com/cpp-tutorial/alias-templates/

## Why it matters
`typedef`/`using` give a name to a single type. An **alias template** parameterizes that name over another type — `using Vec<T> = std::vector<T, MyAllocator<T>>;`. Spelled-out type names like `std::map<std::string, std::vector<int>>::const_iterator` get unmanageable; alias templates trim them to one word at the call site.

## Key points
- Syntax: `template <typename T> using Vec = std::vector<T>;`. Now `Vec<int>` is the same type as `std::vector<int>`.
- Alias templates are **always transparent** — `Vec<int>` and `std::vector<int>` are the same type, no implicit conversion needed.
- They're a *naming* feature only — no new functionality, no overhead.
- Often used to: (a) shorten verbose template instantiations, (b) pin one parameter of a multi-parameter template (`using IntPair = Pair<int>;`), (c) build aliases involving `std::enable_if_t`, `std::conditional_t`, etc., in metaprogramming.

## Code in this folder
- `main.cpp` — alias template that fixes one parameter of `Pair2<T, U>`, plus a generic `Vec<T>` alias for `std::vector<T>`.

## Gotchas
- Alias templates **can't be partially specialized**. If you need that, write a class template with a nested `type`.
- An alias template is not a deduction context the way a class template is — you don't CTAD an alias alone, only the underlying template.

## Run
    make 13.15
