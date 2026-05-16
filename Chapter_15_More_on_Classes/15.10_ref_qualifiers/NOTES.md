# 15.10 — Ref qualifiers

> learncpp.com: https://www.learncpp.com/cpp-tutorial/ref-qualifiers/

## Why it matters
A `const` member function can be called on `const` *and* non-const objects, on lvalues *and* rvalues. **Ref qualifiers** (`&` and `&&` after the parameter list) split that: you can write one overload for "called on an lvalue" and another for "called on an rvalue." This solves the 14.7 dangling-reference problem: a getter can refuse to hand out an internal reference when the host object is a temporary.

## Key points
- `&`-qualified member function: callable only on **lvalues**.
- `&&`-qualified: callable only on **rvalues** (temporaries, results of `std::move`).
- Without a ref qualifier, the function works on both — the existing default.
- Once you write *any* ref-qualified overload, you typically need both (`&` and `&&`), since they no longer fall through.
- Common pattern: `T& data() &;` returns a ref to internal storage; `T data() &&;` returns by *value* (moves the data out) — preventing dangling on temporaries.

## Code in this folder
- `main.cpp` — `Box` with `data()` overloaded by ref qualifier: lvalue → const ref, rvalue → by-value move.

## Gotchas
- The `&` and `&&` here are about the **object the method is called on**, not the parameters. Don't confuse with rvalue reference parameters.
- Compilers may give terse errors when calls hit the wrong overload. Read the qualifier in the error message — `<method> &` vs. `<method> &&`.

## Run
    make 15.10
