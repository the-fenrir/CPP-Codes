# 22.3 — Move constructors and move assignment

> learncpp.com: https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/

## Why it matters
The copy constructor duplicates the resource. For a class that owns a heap allocation (or a file handle, or a socket), that's expensive — and pointless when the source is a temporary about to be destroyed. The **move constructor** (`Foo(Foo&&)`) and **move assignment** (`Foo& operator=(Foo&&)`) let you transfer the resource instead of copying it. The compiler picks the move overload automatically whenever the source is an rvalue.

## Key points
- Signatures: `Foo(Foo&& other) noexcept` and `Foo& operator=(Foo&& other) noexcept`. Mark them `noexcept` so containers (e.g. `std::vector`) will actually use them on reallocation.
- A move ctor **transfers** owned resources from `other` and leaves `other` in a valid empty state — its destructor must remain safe to run.
- Rule of five: if you write any of { dtor, copy ctor, copy assign, move ctor, move assign }, you usually need to consider all five. Otherwise the compiler-generated ones may do the wrong thing.
- **Rule of zero**: prefer to own resources through types that already do this correctly (`std::unique_ptr`, `std::vector`, `std::string`) so you don't write any of the five.
- Compiler **does not** generate move operations if you've declared any of: copy ctor, copy assign, move ctor, move assign, dtor. Be explicit (`= default` or write them) once you've declared any.
- Self-move assignment must not corrupt state — either check `this != &other` or write it move-and-swap style.

## Code in this folder
- `main.cpp` — an `Auto_ptr3<T>` that has both copy (deep) and move (transfer) operations, with cout breadcrumbs so you can see which one runs in which expression.

## Gotchas
- After `std::move(x)`, `x` is *valid but unspecified*. You can assign to it or destroy it; don't assume anything about its contents.
- `noexcept` is not optional. `std::vector<Foo>::resize()` will fall back to copy if your move ctor isn't `noexcept` — silently negating the whole optimization.
- Returning a *local* by value calls the move ctor only when copy elision *doesn't* apply. Don't `return std::move(local)` — that disables NRVO and is usually a pessimization.

## Run
    make 22.03
