# 17.4 — `std::array` of class types, and brace elision

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdarray-of-class-types-and-brace-elision/

## Why it matters
`std::array<House, 3>` works like any other array — but the initializer syntax gets noisy because `std::array` is itself an aggregate wrapping a C-style array. You write *two* sets of braces in the strict form. The language lets you elide the inner braces under specific rules, which is why most code only writes one set. Knowing when elision applies prevents the confused "why doesn't this initializer compile?" loop.

## Key points
- A `std::array<Foo, N>` of an aggregate type initializes strictly with: `std::array<Foo, 2> a {{ {a0_args}, {a1_args} }};` — **double outer braces** because `std::array` wraps a C-style `Foo[N]` member, then inner braces for each `Foo` aggregate.
- **Brace elision** lets you drop the inner-most pair when the element type is itself an aggregate and you're using `Foo{...}` element syntax: `std::array<Foo, 2> a { Foo{...}, Foo{...} };`. The compiler recognizes the wrapped C-style array and absorbs the outer pair.
- Dropping just *one* layer of braces is fiddly and triggers `-Wmissing-braces` on some compilers — and on clang in C++20 mode it's a hard error for the form `{ { a, b }, { a, b } }` (no `Foo`, no double-brace) because clang can't pick which layer the inner braces belong to. Pick one of two safe forms: strict double-brace, or `Foo{...}` per element.
- CTAD works with class types: `std::array a { Foo{1}, Foo{2}, Foo{3} };` deduces `std::array<Foo, 3>`.
- Same rules apply to `constexpr std::array<Foo, N>` if `Foo` has a `constexpr` constructor.

## Code in this folder
- `main.cpp` — defines a small `House` struct, initializes a `std::array<House, 3>` with the strict double-brace form, the elided form, and the explicit-element form; prints them.

## Gotchas
- Brace elision is **only** for aggregate-like initialization. If the element type needs a non-aggregate constructor call, you need explicit `Foo{...}` constructions.
- Mixing elided and non-elided in the same initializer reads badly. Pick one style per declaration.
- Old GCC/Clang versions emitted warnings about missing braces (`-Wmissing-braces`) even when elision was valid. Modern versions don't.

## Run
    make 17.04
