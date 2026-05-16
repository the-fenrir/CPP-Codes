# Chapter 14 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-14-summary-and-quiz/

## One-page recap

### Classes vs. structs
- Both bundle data + functions; **`class` defaults to `private`, `struct` to `public`** — only language-level difference.
- Convention: `struct` for plain aggregates with no invariants, `class` for everything else.

### Access control & encapsulation (14.5–14.8)
- `public:` = interface; `private:` = implementation. Access is **per-class**, not per-object.
- Encapsulation buys you: invariants, refactor freedom, stable interface — visible *over time*, not on day one.
- Don't reflexively pair every private member with a public `get_X/set_X`. Model operations the caller actually performs.

### `const` member functions (14.4, 14.7)
- A `const` object can only call `const` member functions. Default to `const` on accessors.
- Returning `const T&` from a getter avoids copies — but the reference dies with the object.
- A `const` member function may not return non-const refs to members. Compiler enforces.

### Constructors (14.9–14.13)
- Same name as class, no return type. Auto-runs at construction.
- **Member initializer list** is the correct way to set members (`Foo() : m_x{ 0 } {}`). Required for `const`/reference members. Order = declaration order.
- **Default constructors**: implicit unless you declare any constructor; bring it back with `Foo() = default;`. Default args + one constructor can cover all cases.
- **Delegating constructors**: route work through one "real" constructor with `Foo() : Foo{ 0, 0 } {}`. Don't also init other members in that list.
- **Temporaries**: unnamed objects living until the end of the full expression. Bind to `const&` (extends lifetime) and `&&`, not to `T&`.

### Copy & conversion (14.14–14.16)
- **Copy constructor** `Foo(const Foo&)` runs on `Foo b = a;`, pass-by-value, return-by-value.
- Default member-wise copy is wrong for classes owning raw pointers — prefer smart pointers / RAII.
- **Copy elision**: C++17 makes elision mandatory for prvalues (`Foo f = makeFoo();` — no copy). NRVO covers named locals (optional but typical).
- A 1-arg constructor is a **converting constructor**. Make it `explicit` by default; drop `explicit` only when the conversion is genuinely intuitive.

### constexpr classes (14.17)
- `constexpr` constructor + `constexpr` member functions ⇒ compile-time objects.
- Aggregates with literal members are usable in constant expressions for free.
- `static_assert` is your test harness for these.

## Quiz

1. **Q1a** — `Point2d` with `double m_x{0}`, `double m_y{0}`, constructor, `print()`.
2. **Q1b** — Add `distanceTo(const Point2d& other) const`.
3. **Q2** — Convert a `Fraction` struct from prior lessons into a class with member functions.
4. **Q3** — Why `explicit` on the `Fraction` constructor?
5. **Q4** — Why `getFraction()` and `print()` might be better as non-members.

See `quiz_solutions.cpp` for code answers. For the discussion answers:

- **Q3:** `Fraction` accepts an `int` numerator. Without `explicit`, any int silently converts to a `Fraction` — `void multiply(Fraction);` would then accept `multiply(5);` and quietly mean `multiply(Fraction{5, 1})`. That's almost never what the caller intended; `explicit` forces the conversion to be visible at the call site.
- **Q4:** Non-member functions improve encapsulation: anything that can be implemented using only the public interface should be a non-member (Scott Meyers' rule). It keeps the class's surface area small, makes member functions easier to identify as the "core" API, and means you can extend the type's operations without touching the class.

## Run

    make 14.x
