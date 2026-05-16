# 14.16 — Converting constructors and the `explicit` keyword

> learncpp.com: https://www.learncpp.com/cpp-tutorial/converting-constructors-and-the-explicit-keyword/

## Why it matters
A constructor that can be called with one argument doubles as a **type conversion**: `Foo` accepts an `int`, so the language will quietly turn an `int` into a `Foo` *anywhere* a `Foo` is expected. Sometimes that's lovely (`std::string s = "hi";`). Often it's a footgun (`bool b = SomeBigClass{};`). **`explicit`** turns the implicit conversion off, requiring the caller to ask for it.

## Key points
- A single-argument constructor (or multi-arg where all but one have defaults) is a **converting constructor**.
- The compiler will use it for **one implicit conversion step** at a call site — chained implicit conversions are not allowed.
- Mark with `explicit` to forbid implicit use: `explicit Foo(int x);`. Callers must write `Foo{ x }` or `static_cast<Foo>(x)`.
- **Rule of thumb:** make single-arg constructors `explicit` by default. Drop `explicit` only when an implicit conversion is genuinely intuitive.
- Brace initialization with `=` (copy-list-init) is forbidden for `explicit` constructors: `Foo f = { 5 };` won't compile if `Foo(int)` is `explicit`. `Foo f{ 5 };` still works.

## Code in this folder
- `main.cpp` — same class with and without `explicit`; shows the surprising implicit conversion that `explicit` blocks.

## Gotchas
- Conversion through a chain (`int` → `Foo` → `Bar`) doesn't happen implicitly. Beginners try this and get baffled.
- C++20 `explicit(bool)` lets you make the conversion conditional in templates (advanced).

## Run
    make 14.16
