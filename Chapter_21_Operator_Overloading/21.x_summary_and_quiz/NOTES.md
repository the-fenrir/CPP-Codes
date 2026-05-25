# Chapter 21 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-21-summary-and-quiz/

## One-page recap

### What operator overloading is (21.01)
- An overload is just a function named `operator?`. `a + b` ⇒ `operator+(a, b)` (free) or `a.operator+(b)` (member).
- You can't invent operators, change arity, change precedence, or overload between two builtins.
- Don't overload `&&`, `||`, `,` — you lose short-circuit / sequencing.

### Where the overload lives (21.02 → 21.05)
- **Member** — must: `=`, `[]`, `()`, `->`. Should: compound assignment (`+=`), pre/post `++`/`--`, anything that mutates `*this`.
- **Non-member friend** — when the left operand is a foreign type (`5 + Cents`) or when you need to peek at privates from a symmetric op.
- **Non-member non-friend** — default for binary ops you can express through the public API. Smallest blast radius.
- **Must be non-member**: `<<`, `>>` (left operand is the stream).

### I/O operators (21.04)
- `ostream& operator<<(ostream&, const T&)` and `istream& operator>>(istream&, T&)`. Return the stream by reference for chaining.

### Unary ops (21.06)
- `T operator-() const` etc. Single member, returns new value. Don't mutate `*this`.

### Comparison (21.07)
- C++20: `auto operator<=>(const T&) const = default;` + `bool operator==(const T&) const = default;` → all six relational operators.
- Pick the right return category: `strong_ordering` / `weak_ordering` / `partial_ordering` (NaN forces partial).

### `++` / `--` (21.08)
- Prefix: `T& operator++();` mutate, return self.
- Postfix: `T operator++(int);` save old, mutate, return old. Dummy `int` disambiguates.

### `operator[]` and `operator()` (21.09, 21.10)
- Both must be members.
- `[]`: provide both `T&` and `const T&` overloads. Return by reference so `arr[i] = x;` works.
- `()`: arbitrary arity, arbitrary return — functors / stateful callables / matrix indexing.

### Typecasts (21.11)
- `explicit operator T() const` — opt-in conversion *from* your class *to* `T`.
- `explicit operator bool()` is the standard "is this object valid/non-empty" form (`std::optional`, `std::unique_ptr`, streams).

### Assignment / copy (21.12, 21.13)
- `T& operator=(const T&)` — member, self-assignment check, return `*this`.
- **Rule of three / five**: if you write any of {dtor, copy ctor, copy=}, write all three (plus the two move ones).
- Better: don't own raw memory. `unique_ptr`/`vector`/`string` give correct deep copy or non-copyability for free.

### Templates (21.14)
- Templates demand operators at instantiation. Giving your class the standard set (`==`, `<=>`, `<<`, copy/move) makes it fit `std::sort`, `std::set`, `std::map`, range algorithms for free.

---

## Quiz

### Q1 — Which form for each operator on `Point`?

For each of these expressions, should `operator?` be a member or a normal/friend non-member?

a) `point + point`
b) `-point`
c) `std::cout << point`
d) `point = 5;`

**Answers.**
- **a) `point + point` → non-member (friend or plain)**. Binary, symmetric. Member form is legal (`Point::operator+(Point)`) but the non-member form is preferred — it lets you also write `5 + point` if `Point` is constructible from `int`, and it doesn't bias toward the left operand.
- **b) `-point` → member**. Unary, one operand which is the object itself. Members are the natural form for unary operators; nothing is gained by making it a free function.
- **c) `std::cout << point` → must be non-member**. The left operand is `std::ostream`, which you can't add member functions to. Make it a friend if it needs private access.
- **d) `point = 5;` → must be member**. The assignment operator `=` is one of the four that the language requires to be a member function (along with `[]`, `()`, `->`).

### Q2 — `Average` class

Write a class `Average` that tracks the running average of `int`s passed to it via `+=`. The following program must compile, run, and produce the expected output:

```cpp
int main()
{
    Average avg{};
    std::cout << avg << '\n';

    avg += 4;
    std::cout << avg << '\n';

    avg += 8;
    std::cout << avg << '\n';

    avg += 24;
    std::cout << avg << '\n';

    avg += -10;
    std::cout << avg << '\n';

    (avg += 6) += 10;
    std::cout << avg << '\n';

    Average copy{ avg };
    std::cout << copy << '\n';

    return 0;
}
```

Expected output:

```
0
4
6
12
6.5
7
7
```

Implementation hints:
- Track `m_total` (sum of all values added) and `m_count` (how many).
- `operator+=` is a **member**; returns `Average&` so chained / re-chained calls work.
- `operator<<` is a **non-member** (friend if needed). Prints `m_total / m_count`. Decide what to print when `m_count == 0` (the test wants `0`).

### Q3 — `IntArray` with deep copy

Write a dynamic-size `IntArray` so this program compiles and prints two identical rows:

```cpp
IntArray fillArray()
{
    IntArray a{ 5 };
    a[0] = 5;  a[1] = 8;  a[2] = 2;  a[3] = 3;  a[4] = 6;
    return a;
}

int main()
{
    IntArray a{ fillArray() };
    std::cout << a;

    auto b{ a };
    a = a;        // self-assignment must not crash
    b = b;        // ditto

    std::cout << b;

    return 0;
}
```

Expected output:

```
5 8 2 3 6
5 8 2 3 6
```

Requirements:
- Construct with a size; allocate that many `int`s.
- Subscript operator (both `T&` and `const T&` overloads).
- Copy constructor + copy assignment must do **deep** copy.
- Copy assignment must handle self-assignment.
- Destructor releases the allocation.
- Non-member `operator<<` prints elements separated by spaces, trailing newline.

### Q4 — `FixedPoint2`: fractional numbers with 2 decimals

Build a class that represents fixed-point decimal numbers with **exactly two decimal places**, supporting the range `-32768.99` to `32767.99`. Step-by-step:

**Step 1.** Choose member variables. A `std::int16_t` for the integer part (`-32768..32767`) and a `std::int8_t` for the fractional part (`-99..99`) gives the required range with the smallest footprint. Both members must independently carry the sign (or you must enforce that they agree).

**Step 2.** Constructor `FixedPoint2(std::int16_t base, std::int8_t decimal)`. If either argument is negative, both members should end up negative (so `-2` and `+5` becomes base=`-2`, decimal=`-5`, representing `-2.05`). Add an `operator<<` so the test can print:

```
FixedPoint2 a{ 34, 56 };   // 34.56
FixedPoint2 b{ -2, 5 };    // -2.05
FixedPoint2 c{ 2, -5 };    // -2.05
FixedPoint2 d{ -2, -5 };   // -2.05
FixedPoint2 e{ 0, -5 };    // -0.05  (note: integer is 0 but value is negative)
```

**Step 3.** Decimal overflow. If `decimal` is outside `-99..99`, carry into `base`. Example: `FixedPoint2{1, 104}` → `2.04`, not `1.104`. Do this in the constructor.

**Step 4.** Add a constructor `FixedPoint2(double d)` that rounds to 2 decimal places. `0.05` rounds to `0.05`; `-0.048` rounds to `-0.05`; `106.9978` rounds to `107.00`.

**Step 5.** Add:
- `operator==` (compare both members).
- `operator>>` reading a `double` and using the double constructor.
- Unary `operator-` (negate both members).
- Binary `operator+` (do it in `double` for simplicity, then construct a new `FixedPoint2`).

The reference `main()` should be able to do things like `std::cin >> fp; std::cout << "You entered: " << fp;` and `FixedPoint2 a{ 0.75 } + FixedPoint2{ 1.23 }` and have the answer print as `1.98`.

---

## Run

    make 21.x

`quiz_solutions.cpp` is the worked code for Q2, Q3, and Q4, with inline commentary marking the design decisions (why `+=` is a member, why the IntArray copy ctor allocates, why the FixedPoint2 ctor normalises signs).
