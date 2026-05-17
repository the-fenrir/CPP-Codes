# Chapter 13 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-13-summary-and-quiz/

## One-page recap

### Program-defined types (13.1)
- Built-in types end at `int`/`double`/`bool`/`char`. *Program-defined* types (`enum`, `enum class`, `struct`, `class`, `union`) name new types you control.
- Type definitions belong in headers; ODR allows identical definitions across TUs.
- Convention: type names start with a capital letter (`Color`, `Fraction`).

### Enums (13.2–13.6)
- **Unscoped** `enum`: enumerators leak into enclosing scope; implicit conversion to `int`. Useful, dangerous.
- Underlying type: implementation-defined for plain `enum`, defaults to `int` for `enum class`. Fix it: `enum class Color : std::uint8_t { ... };`.
- **Int → enum** is never implicit — `static_cast<E>(x)`.
- **Enum → string**: `switch` returning `std::string_view` over literals.
- **`operator<<` overload** = idiomatic printing. Free function, returns the stream by reference.
- **`enum class`** (scoped): no leakage, no implicit int conversion, type-safe comparisons. Default choice for new enums.
- C++20 `using enum`: bring scoped enumerators into local scope where context is clear.

### Structs (13.7–13.12)
- A `struct` bundles named data members. Access with `.`; access through pointer with `->`.
- **Aggregate init** maps a brace list to members in declaration order. Empty braces value-initialize. Designated initializers (C++20) name them.
- **Default member initializers** (`int x{ 0 };`) close the "uninitialized built-in" footgun. Always use brace initializers.
- **Pass `const T&`, return by value.** For tiny PODs (~one or two scalars), by-value is fine.
- A struct can contain another struct (composition) or an array. `sizeof(S)` includes padding; member order can change it.
- A pointer-to-struct uses `->`; a reference-to-struct uses `.`. `*p.x` is a parsing trap — write `p->x`.

### Templates (13.13–13.15)
- **Class template**: a type parameterized over `T`. `Pair<int>` and `Pair<double>` are distinct, unrelated types.
- **CTAD** (C++17) deduces template arguments from constructor arguments — `Pair p{ 1, 2 };`. C++17 aggregates needed a deduction guide; C++20 doesn't.
- **Alias template**: `template <typename T> using Vec = std::vector<T>;`. Transparent — `Vec<int>` *is* `std::vector<int>`.
- Class templates live in headers — the compiler must see the template definition at every instantiation.

### The `Fraction` thread (13.10 → Ch. 14)
- 13.10 introduces `struct Fraction { int numerator{0}; int denominator{1}; };` with three free functions: `getFraction`, `multiply`, `printFraction`.
- Chapter 14's quiz converts those free functions into member functions of a `Fraction` *class* — and then asks whether that conversion was actually a good idea. Worth re-reading 13.10's signatures before you start that quiz.

## Quiz

### Q1 — Monster struct

Design a struct that represents a monster in a game. It must have:
- a **type** (one of: ogre, dragon, orc, giant spider, slime),
- a **name** (`std::string`),
- **health points** (an `int`).

Provide a `printMonster()` function and use it on:
- an Ogre named "Torg" with 145 health,
- a Slime named "Blurp" with 23 health.

Expected output:

```
This Ogre is named Torg and has 145 health.
This Slime is named Blurp and has 23 health.
```

### Q2 — Pass by value, const ref, or const address?

For each type below, say which call convention you'd use **assuming no modifications** to the argument.

a) `char`
b) `std::string`
c) `unsigned long`
d) `bool`
e) An enumerated type (e.g. `Color`)
f) A struct `Position` with three `double` members
g) A struct `Player` "currently under development" with a single `int` member
h) `int` (when *null* is a valid input — i.e. the function needs to distinguish "no value" from "the value 0")
i) `std::string_view`

**Answers:**

a) `char` — **by value**. One byte; cheaper than a reference, no aliasing concerns.
b) `std::string` — **by const reference**. Strings can hold arbitrarily long buffers; copying is expensive.
c) `unsigned long` — **by value**. Built-in scalar, fits in a register.
d) `bool` — **by value**. One byte.
e) An enumerated type — **by value**. Backed by an integer; trivial to copy.
f) `Position` (3 × double) — **by const reference**. 24 bytes; worth a reference over a copy.
g) `Player` (1 × int, *under development*) — **by const reference**. The size will grow; using `const&` now means you don't have to chase callsites later when fields are added.
h) `int` where null is valid — **by const address (`const int*`)**. The pointer can be `nullptr`, which is how you encode "no value." A `const int&` can't be null.
i) `std::string_view` — **by value**. It's already a view (a pointer + length); copying it is just copying those two members.

### Q3 — `Triad` class template

Design a class template named `Triad` with three members all of the same type `T`. Provide a function template `print(const Triad<T>&)` that prints `[a, b, c]` for the three members.

This code must compile (using CTAD) and produce this output:

```
[1, 2, 3][1.2, 3.4, 5.6]
```

```cpp
int main()
{
    Triad t1{ 1, 2, 3 };           // CTAD → Triad<int>
    print(t1);

    Triad t2{ 1.2, 3.4, 5.6 };     // CTAD → Triad<double>
    print(t2);

    return 0;
}
```

Notes:
- Under C++17 you need a deduction guide for an aggregate `Triad`. Under C++20 you don't. The solution provides one anyway — it's harmless and documents intent.

## Run

    make 13.x

`quiz_solutions.cpp` contains worked code for Q1 and Q3, with inline commentary explaining each design choice (Q2 is a discussion question, answered above).
