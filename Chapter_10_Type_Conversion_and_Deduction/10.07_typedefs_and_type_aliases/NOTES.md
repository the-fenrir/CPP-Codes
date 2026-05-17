# 10.7 — Typedefs and type aliases

> learncpp.com: https://www.learncpp.com/cpp-tutorial/typedefs-and-type-aliases/

## Why it matters
Types like `std::vector<std::pair<std::string, int>>::const_iterator` are not fun to type, and `double` doesn't tell the reader whether you mean degrees or radians. **Type aliases** give an existing type a second, local name. They cost nothing at runtime, they cost nothing at compile time, and they pay for themselves in readability the first time you change the underlying type.

## Key points
- Two syntaxes for the same idea:
  - C-style: `typedef double Distance;`
  - C++11 `using`: `using Distance = double;`  ← prefer this; reads left-to-right and plays better with templates.
- An alias is **not a new type**. `using Radians = double;` and `using Degrees = double;` are the *same type*. The compiler will happily let you assign one to the other.
- Common uses:
  - Shorten unwieldy library types (`using IterT = std::vector<int>::iterator;`).
  - Document intent at signatures (`Radians convert(Degrees);`).
  - Centralize a "size" or "id" type so you can change `int → std::size_t` in one place.
- Aliases obey normal scoping rules — file scope, namespace scope, inside a class. Inside a class, an alias becomes part of the class's public API (`Container::value_type`).

## Code in this folder
- `main.cpp` — both syntaxes; demonstrates that two aliases for `double` are interchangeable; uses an alias to shorten a long standard-library type.

## Gotchas
- Aliases give **no type safety**. If you want a real distinct `Degrees` vs `Radians`, you need a tiny wrapper struct (or a strong-typedef library). The compiler will not catch the mix-up via aliases.
- Don't alias trivially: `using Int = int;` adds noise without information. Aliases earn their keep when they (a) shorten or (b) name an intent the original type doesn't carry.
- Prefer `using` over `typedef` for new code — same semantics, cleaner syntax, supports template aliases.

## Run
    make 10.07
