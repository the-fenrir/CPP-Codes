# Chapter 22 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-22-summary-and-quiz/

## One-page recap

### The two problems being solved
- **Ownership** of heap objects — who calls `delete`? Smart pointers tie ownership to scope (RAII).
- **Pointless copies** of resource-owning objects — move semantics lets the language transfer instead of duplicate.

### R-value references (22.2)
- `T&&` binds only to rvalues. Distinct overload from `T&` / `const T&`.
- A *named* `T&&` parameter is itself an lvalue — use `std::move` to pass it onward as an rvalue.

### Move ctor / move assign (22.3)
- Signatures `Foo(Foo&&) noexcept` and `Foo& operator=(Foo&&) noexcept`. Mark `noexcept` so `std::vector` etc. will use them.
- Move = transfer ownership + leave source in a valid, destructible empty state.
- Rule of five vs. rule of zero — prefer rule of zero by composing types that already do the right thing (`unique_ptr`, `vector`, `string`).
- Self-assignment guard required (`if (this != &other)`), or write it move-and-swap style.

### `std::move` (22.4)
- Just a cast to `T&&`. No movement happens until a move ctor/assign actually runs.
- After `std::move(x)`, `x` is *valid but unspecified*. Don't read it.
- Don't `return std::move(local)` — inhibits NRVO.

### `std::unique_ptr` (22.5)
- One owner. Move-only. Same size as a raw pointer (with stateless deleter).
- Build with `std::make_unique<T>(args)`. Default smart pointer — reach for it first.
- Pass to functions: by value to transfer ownership, by `T&`/`T*` if no ownership needed.

### `std::shared_ptr` (22.6)
- Multiple owners via atomic reference count. ~2× the size of a raw pointer; not free.
- Build with `std::make_shared<T>(args)` — one allocation, exception-safe.
- **Never** build two `shared_ptr`s from the same raw pointer — each gets its own control block ⇒ double-delete.
- Use only when ownership genuinely is shared.

### `std::weak_ptr` and cycles (22.7)
- Two `shared_ptr`s pointing at each other never reach refcount 0 — leak.
- Make the back-edge a `weak_ptr`. Forward edge stays `shared_ptr`.
- `weak_ptr` doesn't extend lifetime. `lock()` to obtain a temporary `shared_ptr`; check for null.

### What smart pointers do *not* fix
- They don't dodge cycles (need `weak_ptr`).
- They don't help if you build them from the wrong source (raw pointer, or `this`).
- They don't make ownership decisions for you — they encode the decision you already made.

## Quiz

### Q1 — When to use each smart pointer

**Q1a — `std::unique_ptr`.**
Sole-ownership smart pointer. Use whenever a heap object has exactly one owner — which is most of the time. Move-only; cheap; same size as `T*`. This should be your default; pick the others only if you've justified the upgrade.

**Q1b — `std::shared_ptr`.**
Shared ownership via atomic refcount. Use when an object truly has multiple owners and you can't statically decide which one outlives the others — e.g. an object in two independent caches, a node referenced from multiple containers. The object is destroyed when the last `shared_ptr` is gone. Cost: two pointer-sized members, atomic refcount ops, and the control-block allocation (one allocation total when you use `make_shared`).

**Q1c — `std::weak_ptr`.**
Non-owning observation of a `shared_ptr`-managed object. Doesn't affect refcount. Use to break cycles (back-edges in a graph of `shared_ptr`s), and as a "maybe still alive" handle (caches, observers). Always go through `.lock()` and check the result for null — that's the only safe way to dereference.

**Q1d — `std::auto_ptr`.**
Don't. Deprecated in C++11, removed in C++17. Its "copy = transfer" behavior was a permanent footgun; `std::unique_ptr` replaces it cleanly with move semantics.

### Q2 — Why move semantics focuses on r-values

R-values are temporaries — by definition the program has no further use for them after the current expression. Copying their contents to a destination and then immediately destroying the original is pure waste; the resource will be freed anyway. With move semantics the destination *steals* the temporary's resources (transfers the heap pointer, takes the file handle, etc.) and leaves the temporary empty. The empty temporary is destroyed harmlessly, and the destination saved a deep copy. The mechanism is rvalue-references (`T&&`) overloads: the compiler statically routes "the source was a temporary" into the cheaper path, and lvalues continue to use the copying path unchanged.

### Q3 — Two `shared_ptr`s from one raw pointer

**Original (buggy) code:**
```cpp
#include <iostream>
#include <memory>

class Resource {
public:
    Resource()  { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main() {
    auto* res{ new Resource{} };
    std::shared_ptr<Resource> ptr1{ res };
    std::shared_ptr<Resource> ptr2{ res }; // BUG
}
```

**What's wrong.** `ptr1` and `ptr2` are each constructed from the same *raw* pointer. Each `shared_ptr` constructed from a raw pointer creates its **own** control block and refcount of 1. Neither knows the other exists. When the program exits, both try to delete the same object — undefined behavior (typically double-free / heap corruption).

**Fix.** Use `std::make_shared` for the first owner, and copy *that smart pointer* to share. Then both pointers see the same control block, and the refcount goes 1 → 2 → 0 in a controlled way:

```cpp
#include <iostream>
#include <memory>

class Resource {
public:
    Resource()  { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main() {
    auto ptr1{ std::make_shared<Resource>() };
    auto ptr2{ ptr1 };                       // shares ptr1's control block
}
```

`make_shared` also gives you a single allocation for the object + control block (cheaper) and is exception-safe versus the `shared_ptr<T>{ new T }` form. Rule of thumb: **never hand a raw `new` to a smart-pointer constructor**, and never build two smart pointers from the same raw pointer.

## Run

    make 22.x

`quiz_solutions.cpp` contains the runnable fix for Q3 plus a short demo showing `use_count()` going 1 → 2 → 0 correctly. Q1 and Q2 are discussion answers in this file.
