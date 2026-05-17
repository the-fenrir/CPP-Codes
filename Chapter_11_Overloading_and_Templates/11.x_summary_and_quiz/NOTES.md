# Chapter 11 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-11-summary-and-quiz/

## One-page recap

### Overloading (11.1–11.3)
- Same name, different parameter lists. Resolution at compile time.
- Differentiation: number of params, types of params (low-level `const` counts, top-level `const` on by-value doesn't), or member-function `const` / ref-qualifiers. **Return type alone never differentiates.**
- Resolution tiers: exact match → promotion → standard conversion → user-defined conversion → ellipsis. First tier with exactly one match wins; ties at the same tier are **ambiguous**.

### Deleting functions (11.4)
- `void f(SomeType) = delete;` keeps the overload visible but makes selecting it a compile error. Use to block a silent conversion path.

### Default arguments (11.5)
- Rightmost params only. Declared once (usually in the header). Do **not** differentiate overloads — mixing them with overloads is the easiest way to write an ambiguous call.

### Function templates (11.6–11.8)
- `template <typename T> T f(T)` — one description, instantiated per type.
- Template argument deduction: no conversions. `f(1, 2.0)` with shared `T` fails. Fix with explicit `f<double>(1, 2.0)` or two type parameters.
- C++20 abbreviated form: `auto f(auto x, auto y)` — each `auto` is its own template parameter.
- `auto` return type when the result type depends on the inputs.

### Instantiation (11.7)
- Each `T` (or `T,U`) combination ⇒ separate function, separate `static` locals.
- Overload set: a non-template overload with an exact match beats a template that would also match.

### Non-type template parameters (11.9)
- Parameters that are *values*, not types: `std::array<int, 16>`, `Factorial<5>`. Must be constant expressions.
- C++20 lets you write `template <auto N>` to deduce the type.

### Multi-file templates (11.10)
- Definitions must be visible at every call site → **templates live in headers**. Putting a template body in a `.cpp` yields linker errors.

## Quiz

### Q1a — overload resolution with `short`

What does this program print?

```cpp
#include <iostream>

void print(int x)    { std::cout << "int "    << x << '\n'; }
void print(double x) { std::cout << "double " << x << '\n'; }

int main() {
    short s{ 5 };
    print(s);
}
```

**Answer.** `int 5`. `short` → `int` is a **promotion** (tier 2); `short` → `double` is a **standard conversion** (tier 3). Promotion beats conversion, so `print(int)` wins.

### Q1b — why this doesn't compile

```cpp
#include <iostream>

void print()           { std::cout << "void\n"; }
void print(int x = 0)  { std::cout << "int "    << x << '\n'; }
void print(double x)   { std::cout << "double " << x << '\n'; }

int main() {
    print(5.0f);   // (1)
    print();       // (2)
}
```

**Answer.** Line (2) is ambiguous. `print()` matches `void print()` directly *and* matches `void print(int = 0)` via the default argument. Default arguments don't differentiate overloads, so the compiler can't pick. Line (1) on its own would be fine (`float` → `double` promotion).

### Q1c — why this doesn't compile

```cpp
#include <iostream>

void print(long x)   { std::cout << "long "   << x << '\n'; }
void print(double x) { std::cout << "double " << x << '\n'; }

int main() { print(5); }
```

**Answer.** Ambiguous match. `int` → `long` and `int` → `double` are both *standard conversions* (same tier). Neither is better than the other, so resolution fails. Adding `print(int)` or casting at the call site (`print(5L)` or `print(5.0)`) resolves it.

### Q2 — write some templates

**Step 1.** Write a template `add(T, T)` that returns the sum.

```cpp
template <typename T>
T add(T x, T y) { return x + y; }
```

`add(2, 3)` → `5`, `add(1.2, 3.4)` → `4.6`.

**Step 2.** Write `mult(T, int)` — `T` for the first parameter, plain `int` for the second.

```cpp
template <typename T>
T mult(T x, int y) { return x * y; }
```

`T` is deduced only from the first argument. `mult(1.2, 3)` ⇒ `T = double` ⇒ `3.6`.

**Step 3.** Write `sub(T, U)` with two independent type parameters and an `auto` return type.

```cpp
template <typename T, typename U>
auto sub(T x, U y) { return x - y; }
```

`sub(4, 1.5)` ⇒ `T = int, U = double`, return type deduced as `double` ⇒ `2.5`.

### Q3 — predict the output

```cpp
template <typename T>
int count(T) {
    static int c{ 0 };
    return ++c;
}

int main() {
    std::cout << count(1)         << '\n';   // (a)
    std::cout << count(1)         << '\n';   // (b)
    std::cout << count(2.3)       << '\n';   // (c)
    std::cout << count<double>(1) << '\n';   // (d)
}
```

**Answer.** `1`, `2`, `1`, `2`.

- (a) and (b) instantiate `count<int>`, which has its own `static c`. First call → 1, second → 2.
- (c) instantiates a **different** function, `count<double>`. Its `static c` starts at 0 → returns 1.
- (d) explicitly selects `count<double>` (`1` is converted to `double` first). Same function as (c), so its counter continues: 2.

Per-type instantiation ⇒ per-type statics. This is the "templates are functions, not macros" lesson.

### Q4 — predict the output (template vs. non-template)

```cpp
int foo(int n) { return n + 10; }

template <typename T>
int foo(T n) { return n; }

int main() {
    std::cout << foo(1)        << '\n';   // (a)
    short s{ 2 };
    std::cout << foo(s)        << '\n';   // (b)
    std::cout << foo<int>(4)   << '\n';   // (c)
    std::cout << foo<int>(s)   << '\n';   // (d)
    std::cout << foo<>(6)      << '\n';   // (e)
}
```

**Answer.** `11`, `2`, `4`, `2`, `6`.

- (a) `foo(1)`: non-template `foo(int)` is an exact match, template `foo<int>` is also an exact match. **Non-template wins ties** ⇒ 1 + 10 = **11**.
- (b) `foo(s)`: non-template requires a promotion `short → int`; template can deduce `T = short` with no conversion. Template wins ⇒ **2**.
- (c) `foo<int>(4)`: explicit `<int>` forces a template call; deduction/selection skips the non-template ⇒ **4**.
- (d) `foo<int>(s)`: again explicit template; `s` promotes to `int` ⇒ **2**.
- (e) `foo<>(6)`: empty `<>` still forces a template call (no non-template considered); `T` deduces to `int` ⇒ **6**.

The trick: explicit template syntax (`<T>` or even `<>`) takes the non-template overload out of the running entirely.

## Run

    make 11.x

`quiz_solutions.cpp` walks through Q1a/Q1b/Q1c by code-with-comments (the ambiguous ones are commented out, with the error stated in the comment), implements all three Q2 templates, and reproduces Q3 and Q4 with their expected outputs.
