# Chapter 10 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-10-summary-and-quiz/

## One-page recap

### Conversions the compiler inserts for you (10.1–10.5)
- **Implicit conversion** (10.01): wherever the actual type doesn't match the expected type, the compiler tries to convert.
- **Numeric promotion** (10.02): safe, value-preserving widening. Smaller integral types → `int`; `float` → `double`. Always free, always exact.
- **Numeric conversion** (10.03): everything else between numeric types. *May* lose value or precision. Usually only a warning outside list-init.
- **Narrowing conversion** (10.04): the subset of numeric conversions that can lose info. Forbidden inside `{ ... }` initialization — that's a hard compile error, not a warning. Exception: a `constexpr` source value exactly representable in the destination is not narrowing.
- **Arithmetic conversions** (10.05): the ladder used to pick a common type for binary ops. `long double > double > float > unsigned long long > long long > unsigned long > long > unsigned int > int`. Sub-`int` operands promote to `int` first. **Integer / integer = integer** (this is where the silent bugs live). Mixing signed and unsigned at the same rank converts the signed operand to unsigned.

### Saying "I really do mean this" (10.6)
- `static_cast<T>(expr)` — the safe, named, everyday cast. Use it to:
  - Force one side of `int / int` to `double`.
  - Print a `char` as a number.
  - Suppress a deliberate narrowing inside `{ }`.
- Avoid C-style `(T)x` and functional `T(x)` casts in C++ code — too permissive.
- A cast does not check at runtime. `static_cast<int>(3.9)` is `3` (truncation, not rounding).

### Naming types (10.7)
- `using Name = ExistingType;` is the modern syntax; `typedef` is the legacy one. Same semantics.
- Aliases are *names*, not new types. `Degrees` and `Radians` aliased to `double` are interchangeable — the compiler won't catch a mix-up.
- Earn their keep by (a) shortening, or (b) documenting intent. Don't alias trivially.

### Omitting types (10.8–10.9)
- `auto x = expr;` deduces `x`'s type from `expr`. Drops top-level `const` and references — add `const`, `&`, `const&` explicitly when you want them.
- `auto f() { return ...; }` deduces a function's return type. All returns must agree. Definition must be visible to callers — *don't* `auto`-return public-header functions.
- Trailing return: `auto f(...) -> Type` is equivalent to writing `Type f(...)`. The `-> decltype(...)` form lets the return type depend on the parameter types — essential for templates.

## Quiz

### Q1 — Classify each conversion

For each of the following, name the conversion category:
**no conversion needed**, **numeric promotion**, **numeric conversion**, or **won't compile due to narrowing**.

```cpp
int main()
{
    int a { 5 };                          // 1a
    int b { 'a' };                        // 1b
    int c { 5.4 };                        // 1c
    int d { true };                       // 1d
    int e { static_cast<int>(5.4) };      // 1e

    double f { 5.0f };                    // 1f
    double g { 5 };                       // 1g

    // Extra credit
    long h { 5 };                         // 1h
    float i { f };                        // 1i  (f is the double above)
    float j { 5.0 };                      // 1j
}
```

**Answers.**

| # | Code | Category | Why |
|---|---|---|---|
| 1a | `int a { 5 }`               | No conversion needed                 | `5` is already `int`. |
| 1b | `int b { 'a' }`             | Numeric promotion                    | `char` → `int` is integral promotion, value-preserving. |
| 1c | `int c { 5.4 }`             | Won't compile (narrowing)            | `double` → `int` in brace init; `5.4` isn't exactly representable as `int`. |
| 1d | `int d { true }`            | Numeric promotion                    | `bool` → `int` is integral promotion (`true` → `1`). |
| 1e | `int e { static_cast<int>(5.4) }` | Numeric conversion             | The cast performs `double` → `int`. Brace init accepts it because the cast result is itself an `int`. |
| 1f | `double f { 5.0f }`         | Numeric promotion                    | `float` → `double` is FP promotion, value-preserving. |
| 1g | `double g { 5 }`            | Numeric conversion                   | `int` → `double` is a numeric conversion (not a promotion). Allowed in brace init because `5` is constexpr and exactly representable. |
| 1h | `long h { 5 }`              | Numeric conversion                   | `int` → `long`. Not a promotion (promotions widen sub-`int` types to `int` or `float` to `double`). Brace-init OK because constexpr-exact. |
| 1i | `float i { f }`             | Won't compile (narrowing)            | `double` → `float`; source `f` is not constexpr, so narrowing applies even though the runtime value happens to fit. |
| 1j | `float j { 5.0 }`           | Numeric conversion                   | `double` literal → `float`. Allowed because `5.0` is constexpr and exactly representable in `float`. |

### Q2a — Degree↔Radian with type aliases

Update the program below to use type aliases `Degrees` and `Radians`:

```cpp
#include <iostream>

namespace constants
{
    constexpr double pi { 3.14159 };
}

double convertToRadians(double degrees)
{
    return degrees * constants::pi / 180;
}

int main()
{
    std::cout << "Enter a number of degrees: ";
    double degrees{};
    std::cin >> degrees;

    double radians { convertToRadians(degrees) };
    std::cout << degrees << " degrees is " << radians << " radians.\n";

    return 0;
}
```

See `quiz_solutions.cpp` for the worked version.

### Q2b — Why does `radians = degrees;` compile?

**Discussion question.** With the aliases from Q2a in place, the assignment `radians = degrees;` compiles cleanly with no warning. Why?

**Answer.** `using Degrees = double;` and `using Radians = double;` do not create two new types — they create two *names* for the same underlying `double`. From the compiler's point of view, `radians = degrees;` is `double = double;`, which is a trivially valid assignment. Aliases provide documentation, not type safety: they help a *human* reader see that the units don't match, but the compiler sees nothing wrong.

To actually make the units type-safe, you'd need distinct types — typically tiny wrapper structs:

```cpp
struct Degrees { double v; };
struct Radians { double v; };
Radians convertToRadians(Degrees d) { return { d.v * constants::pi / 180 }; }
```

Now `radians = degrees;` is `Radians = Degrees`, which the compiler rejects unless you explicitly provide a conversion.

## Run

    make 10.x

`quiz_solutions.cpp` contains the worked code for Q2a, plus inline commentary connecting Q2b's "why" to the body of the program.
