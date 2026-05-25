# 22.5 — `std::unique_ptr`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdunique_ptr/

## Why it matters
`std::unique_ptr<T>` is the default smart pointer. It owns one heap object, calls `delete` in its destructor, and is **move-only** — copying is deleted. That single property (exactly one owner) is what makes it cheap (no refcount) and impossible to leak in normal code paths.

## Key points
- Construct with `std::make_unique<T>(args...)` — never `unique_ptr<T>{ new T{...} }` (rare exception-safety footgun in expressions like `f(unique_ptr<A>{new A}, unique_ptr<B>{new B})`).
- API mirrors a pointer: `*p`, `p->`, `bool` conversion checks non-null. `p.get()` returns the raw pointer (don't `delete` it).
- **Copy is deleted; move transfers ownership.** Return `unique_ptr` from factory functions by value — compiler moves it out.
- Passing a `unique_ptr` to a function: take it by value (transfer) or by `const unique_ptr&` (rare). If the function doesn't need ownership, take a raw `T*` or `T&` instead.
- For arrays: `std::unique_ptr<T[]>` uses `delete[]`. Or just use `std::vector<T>`.
- Custom deleters via the second template arg: `std::unique_ptr<FILE, decltype(&fclose)>`.

## Code in this folder
- `main.cpp` — a `Resource`, a factory `make()` returning `unique_ptr` by value, and a consumer that takes ownership. Includes a commented-out copy attempt that would fail to compile.

## Gotchas
- `std::make_unique` is in `<memory>`, C++14. Use it.
- `unique_ptr<T>` is the same size as `T*` only when the deleter is stateless. Custom stateful deleters grow the smart pointer.
- A `unique_ptr` member makes the *containing class* move-only. That's usually what you want; just know it.
- Don't `.get()` a raw pointer and then construct another smart pointer from it. That's the same bug as Q3 in the chapter quiz, just with `unique_ptr` flavor — instant double-delete.

## Run
    make 22.05
