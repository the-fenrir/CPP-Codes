# 22.2 — R-value references

> learncpp.com: https://www.learncpp.com/cpp-tutorial/rvalue-references/

## Why it matters
Move semantics needs a way for the language to say "this thing is a temporary, you can gut it." That's what `T&&` (rvalue reference) is: a reference that binds *only* to rvalues. Overload a function on `const T&` and `T&&` and the compiler routes lvalues to the copying path and rvalues to the moving path automatically.

## Key points
- **lvalue** — has a name / a stable identity / an address. `int x; x = 5;` — `x` is an lvalue.
- **rvalue** — temporary, no name. The result of `x + 1`, `make_thing()`, a literal `5`.
- `T&` binds only to lvalues. `const T&` binds to anything (lvalue *or* rvalue), which is why we've been getting away with it.
- `T&&` (rvalue reference) binds *only* to rvalues. Distinct overload from `T&` / `const T&`.
- Inside a function, a parameter `T&& x` is itself an **lvalue** (it has a name `x`). To pass it onward as an rvalue you must `std::move(x)` (lesson 22.04).
- The whole point: overload on `const T&` vs `T&&` to give rvalues a more efficient path.

## Code in this folder
- `main.cpp` — a function `f` overloaded for `int&`, `const int&`, `int&&`; calls show which overload binds for each kind of expression.

## Gotchas
- "A named rvalue reference is an lvalue." It sounds like wordplay — it's load-bearing. `void g(T&& p)` — inside `g`, `p` has a name, so `p` is an lvalue and binds to the lvalue overload. Use `std::move(p)` if you want to pass it as an rvalue.
- `const T&&` is legal but nearly useless — you can't gut a const object, so there's nothing to gain over `const T&`.
- "Rvalue reference" doesn't mean the *referent* is an rvalue forever — it means at the bind site the expression was an rvalue. After binding, behavior is governed by the reference's type and name.

## Run
    make 22.02
