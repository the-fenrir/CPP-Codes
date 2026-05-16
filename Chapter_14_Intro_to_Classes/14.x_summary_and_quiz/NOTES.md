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

### Q1a — `Point2d` basics

Write a class `Point2d` with two private member variables `m_x` and `m_y` (both `double`, defaulted to `0.0`), a constructor, and a `print()` member function. This program must compile and run:

```cpp
#include <iostream>

int main()
{
    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    // Point2d third{ 4.0 }; // should error if uncommented

    first.print();
    second.print();

    return 0;
}
```

Expected output:

```
Point2d(0, 0)
Point2d(3, 4)
```

Note the commented line: `Point2d third{ 4.0 };` must be a compile error if uncommented — i.e. you should *not* provide a single-`double` constructor.

### Q1b — distance between two points

Add a member function `distanceTo()` that takes another `Point2d` and returns the distance between them using:

```
sqrt((x1 - x2)² + (y1 - y2)²)
```

`std::sqrt` lives in `<cmath>`. This program must work:

```cpp
#include <cmath>
#include <iostream>

int main()
{
    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    first.print();
    second.print();

    std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';

    return 0;
}
```

Expected output:

```
Point2d(0, 0)
Point2d(3, 4)
Distance between two points: 5
```

### Q2 — `Fraction` struct → class

Take this struct + free functions (from lesson 13.10) and convert it into a class where the free functions become member functions:

```cpp
struct Fraction
{
    int numerator{ 0 };
    int denominator{ 1 };
};

Fraction getFraction();                                       // reads from cin
Fraction multiply(const Fraction& f1, const Fraction& f2);    // multiplies two
void     printFraction(const Fraction& f);                    // prints "n/d"
```

> Author's note from learncpp: this exercise *intentionally* breaks the "prefer non-member non-friend functions" guideline — it's testing your ability to convert non-members into members, not testing good design. Q4 below circles back on whether the conversion was actually a good idea.

### Q3 — Why `explicit` on the `Fraction` constructor?

**Discussion question:** In the Q2 solution, why should the `Fraction` constructor be made `explicit`?

**Answer.** `Fraction(int numerator = 0, int denominator = 1)` is a *converting constructor* — single-argument-callable because both parameters have defaults. Without `explicit`, the compiler will silently turn any `int` into a `Fraction` wherever a `Fraction` is expected. So a function `Fraction multiply(const Fraction&, const Fraction&)` would accept `multiply(5, 7)` and quietly interpret it as `multiply(Fraction{5}, Fraction{7})` — i.e. `5/1 * 7/1`, not "multiply five and seven." The call site looks correct but means something different than the caller thinks. `explicit` blocks the implicit conversion, forcing the caller to write `multiply(Fraction{5}, Fraction{7})` if that's truly what they meant — making the intent visible. Rule of thumb: make single-argument-callable constructors `explicit` by default, and drop `explicit` only when the implicit conversion is genuinely intuitive (like `std::string` from `const char*`).

### Q4 — Why keep `getFraction()` and `printFraction()` as non-members?

**Discussion question:** In Q2 you converted three free functions to member functions. Why would it actually be *better* to leave `getFraction()` and `printFraction()` as non-members?

**Answer.** Scott Meyers' guideline: *prefer non-member non-friend functions over member functions when both can do the job*. Three concrete reasons here:

1. **Smaller class surface.** Member functions are part of the class's API; readers infer "these are the things `Fraction` *does*." Stream-style I/O (`print`, `read`) doesn't add a *capability* to `Fraction`, it just formats one — keep it out of the member list so the actual operations (`multiply`, `reduce`, `reciprocal`) stand out.
2. **Extensibility without modifying the class.** Anyone can add their own non-member `printAsDecimal(const Fraction&)` later; nobody can add member functions to a class they don't own. Non-members let `Fraction`'s capabilities grow without re-opening the class.
3. **Encapsulation is preserved, not weakened.** A non-member function can only use the *public* interface — so it depends on exactly what callers depend on. If you can implement an operation using the public interface alone, making it a member buys you nothing and forces the class to take on more responsibility.

`getFraction()` (reads from `std::cin`) and `printFraction()` (writes to `std::cout`) both fall into this category — neither needs private access, neither represents a fundamental operation of a fraction. Leave them outside.

## Run

    make 14.x

`quiz_solutions.cpp` has the worked code for Q1a, Q1b, and Q2, with inline commentary explaining each design choice.
