# Chapter 12 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-12-summary-and-quiz/

## One-page recap

### Value categories (12.2)
- Every expression has a **type** *and* a **value category**.
- **lvalue**: has identity (an address you can take); persists. `x`, `*p`, `arr[0]`, a function call returning `T&`.
- **rvalue**: transient, no usable identity. `5`, `x + 1`, a function call returning `T`.
- Modifiable lvalues may appear on the left of `=`. Const lvalues are still lvalues — just not modifiable.
- Rvalues bind to `const T&` (with lifetime extension) but not to `T&`.

### References (12.3–12.4)
- `T&` is an **alias** for an existing object. Must be initialized. Never rebinds. Cannot be null.
- `ref = other;` assigns `other`'s value into the referenced object — it does *not* rebind.
- `const T&` accepts lvalues, rvalues, temporaries, conversions; extends temporary lifetime. The "accepts anything readable" type.

### Pass-by-reference (12.5–12.6)
- `T&` parameter: function may mutate caller's object; argument must be a modifiable lvalue.
- `const T&` parameter: no copy, no mutation, accepts everything. **Default for non-trivial input parameters.**
- For tiny trivially-copyable types (`int`, `double`, pointer), pass by value.

### Pointers (12.7–12.9)
- A pointer is an object holding an address. Has its own storage. Is rebindable. Can be null.
- `&x` → address-of (rvalue `T*`). `*p` → dereference (lvalue `T`).
- `nullptr` is the canonical null. Never `NULL` or `0` in new code — overload resolution differs.
- Four const combos, read right-to-left: `const T*` (const pointee), `T* const` (const pointer), `const T* const` (both), `T*` (neither).

### Pass-by-address (12.10–12.11)
- `T*` parameter: like `T&` but with explicit null. Use for **optional** parameters; for required inputs prefer `T&`.
- To repoint the caller's pointer, take `T*&` (or `T**`) — repointing a plain `T*` parameter only rebinds locally.
- "Pass-by-address for performance" is the wrong answer — that's `const T&`.

### Return by reference / address (12.12)
- Return by reference is fine when the referent outlives the call (static, member of long-lived object, passed-in reference).
- **Returning a reference to a local is UB.** Same for a parameter passed by value (still a local).
- C++17 mandatory copy elision: return-by-value is free for prvalues. Prefer it.

### In/out parameters (12.13)
- In: value (tiny) or `const T&` (non-trivial).
- Out: **return by value** (use `std::pair`, `std::tuple`, or a struct for multiple). `T&`/`T*` out parameters are a fallback.
- In/out: `T&`.

### Type deduction (12.14)
- `auto` **drops** top-level `const` and references. Use `auto&`, `const auto&`, `auto*` to keep them.
- Pointee `const` (`const int*`) **survives** plain `auto`.
- Range-based for default for reading: `for (const auto& e : v)`.

### `std::optional` (12.15)
- "Maybe a `T`." `if (o)`, `*o`, `o.value()`, `o.value_or(default)`, `std::nullopt`.
- Replaces sentinel-return-values, out-parameter+bool, and most legitimate uses of "nullable input pointer."
- Value stored inline — no heap allocation. Not a smart pointer.

## Quiz

### Q1 — Classify each as lvalue or rvalue

a) `std::cout << 5;` — `5` is an **rvalue** (integer literal).

b) `int x{ 5 }; std::cout << x;` — `x` is an **lvalue** (named object, has identity).

c) `int x{ 5 }; std::cout << x + 1;` — `x + 1` is an **rvalue** (result of `operator+`, no identity).

d) `int foo() { return 5; } std::cout << foo();` — `foo()` is an **rvalue** (returns by value).

e) `int& max(int& x, int& y) { return x > y ? x : y; } int x{5}, y{6}; std::cout << max(x, y);` — `max(x, y)` is an **lvalue** (returns by reference; you could write `max(x, y) = 0;`).

### Q2 — Determine the output

```cpp
int main() {
    int x{ 4 };
    int y{ 6 };
    int& ref{ x };
    ++ref;        // ref is x → x becomes 5
    ref = y;      // ASSIGNS y's value into x → x becomes 6 (ref does NOT rebind to y)
    ++ref;        // ref is still x → x becomes 7; y is untouched
    std::cout << x << ' ' << y;
    return 0;
}
```

Output: `7 6`

The point: `ref = y;` is an *assignment through ref*, not a rebind. After it, `ref` is still an alias for `x`.

### Q3 — Two reasons to prefer `const T&` over `T&`

1. **It expresses the contract.** A non-const reference parameter says "I may modify this." If you don't intend to, `const T&` documents that — readers and reviewers don't have to read the body to know.
2. **It accepts more arguments.** `const T&` binds to const objects, rvalues, temporaries, and convertible types (with lifetime extension); `T&` accepts only modifiable lvalues. So `const T&` is strictly more general for inputs you only read.

(Bonus: `const T&` enables more compiler optimization in some cases because aliasing analysis sees the no-mutation guarantee, and it lets the function be called from `const` contexts.)

### Q4 — Const pointer vs. pointer to const

- A **pointer to const** is `const T*` (or equivalently `T const*`). The pointer itself is modifiable (can be reassigned to a different address); the *pointee* may not be modified through this pointer.
  ```cpp
  int x { 1 }, y { 2 };
  const int* p { &x };
  // *p = 5;   // error: pointee is const through p
  p = &y;      // OK: repoint
  ```

- A **const pointer** is `T* const`. The pointer is itself const (cannot be reassigned to a different address); the pointee is modifiable through it.
  ```cpp
  int x { 1 }, y { 2 };
  int* const p { &x };
  *p = 5;      // OK: pointee not const
  // p = &y;   // error: p is const
  ```

Mnemonic: read right-to-left. `const` left of `*` qualifies the pointee; `const` right of `*` qualifies the pointer. A `const T* const` is both — neither the pointer nor the pointee can change through this name.

### Q5 — `sort2`

Write `void sort2(int& a, int& b)` so that after the call, `a <= b`.

```cpp
void sort2(int& a, int& b) {
    if (a > b) std::swap(a, b);
}
```

- Parameters are non-const lvalue references — required because we mutate the caller's variables.
- `std::swap` (in `<utility>`) is idiomatic; writing it as a manual three-line swap with a temporary is fine for a first implementation.
- The function returns `void` because the result is communicated via the parameters. (An alternative API would return `std::pair<int,int>` — see 12.13 for why that's often preferable. Quiz spec says use references.)

## Run

    make 12.x

`quiz_solutions.cpp` has the runnable code for Q2 and Q5, plus tiny demos for Q3 and Q4 that double as inline commentary.
