# 25.11 — Printing inherited classes using `operator<<`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/printing-inherited-classes-using-operator/

## Why it matters
`operator<<` for streams is a **non-member** function — and non-members can't be virtual. So the obvious "make `operator<<` virtual" doesn't work. The pattern: one non-member `operator<<(ostream&, const Base&)` forwards to a virtual `print(ostream&) const` member. The free function gets to be polymorphic because of what it calls, not what it is.

## Key points
- Pattern (sometimes called the "virtual stream insertion" or "polymorphic operator<<"):
  - Base has `virtual std::ostream& print(std::ostream& out) const;`.
  - Derived overrides `print`.
  - One free function `operator<<(std::ostream& out, const Base& b) { return b.print(out); }`.
- All the virtual-dispatch goodness happens *inside* `print`. The `operator<<` site sees `const Base&`; the call to `b.print(out)` dispatches dynamically.
- Return `std::ostream&` from `print` so chaining works: `out << a << b << '\n';`.
- This pattern composes with the rest of the chapter: `Base` is often abstract (25.07) and the destructor is virtual (25.04), so the only thing left to write per derived is its own `print`.

## Code in this folder
- `main.cpp` — `Shape` abstract base with virtual `print`; `Circle` and `Square` derived; one `operator<<` that handles both. A `std::vector<const Shape*>` round-trip demonstrates correct dispatch.

## Gotchas
- Don't try to make `operator<<` itself a friend that's virtual — virtual only works on member functions.
- Returning `std::ostream&` from `print` is the convention; returning `void` works but breaks chaining (`out << shape << '\n'` won't compile).
- Avoid duplicating logic: it's tempting to write a `Circle::operator<<` overload too. Don't — let the free function be the single entry point and let virtual dispatch do the work.

## Run
    make 25.11
