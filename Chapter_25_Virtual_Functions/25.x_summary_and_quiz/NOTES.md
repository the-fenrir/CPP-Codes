# Chapter 25 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-25-summary-and-quiz/

## One-page recap

### Base ptrs/refs, virtual functions (25.1–25.2)
- A `Base*`/`Base&` can bind to a `Derived` — but a **non-virtual** call resolves statically to `Base`'s version.
- Add `virtual` to the base declaration to get late binding: the call goes to the most-derived override of the dynamic type.
- The override must match signature exactly (return type may be covariant); a near-miss creates an *overload* that hides the base, not an override.

### `override`, `final`, covariance (25.3)
- `override` on every override — compile error if you typo the signature.
- `final` on a virtual function blocks further overriding; on a class it blocks inheritance.
- Covariant return: a virtual `Base* f()` can be overridden by `Derived* f()`. Pointer/reference only, same hierarchy.

### Virtual destructors (25.4)
- If a class is ever deleted polymorphically (through a base pointer), its destructor **must** be virtual — otherwise the derived destructor never runs (UB).
- Default rule: any polymorphic base gets `virtual ~Base() = default;`.
- `Base::foo()` is the explicit-qualifier escape from virtual dispatch; useful for derived overrides that chain to the base implementation.

### Early vs. late binding & the vtable (25.5–25.6)
- Early = compile-time-resolved, late = runtime-resolved.
- Polymorphic classes carry a hidden vptr; each call through a base reference loads vptr, indexes the vtable, calls the slot. One indirection.
- Virtual calls inside ctors/dtors are early-bound to the *current* class — the object isn't fully alive / already partly dead.

### Pure virtuals, abstract & interface classes (25.7)
- `= 0` makes a virtual pure; the class becomes abstract — instantiation is forbidden, derivation is not.
- Every pure virtual must be overridden in a derived class for that derived class to be concrete.
- Interface class = only pure virtuals + virtual dtor, no member data. The C++ way to say "type implementing this protocol."

### Virtual base classes (25.8)
- Diamond inheritance duplicates the shared base. `virtual public Base` in the intermediate classes deduplicates to one shared sub-object.
- The most-derived class is responsible for constructing the virtual base — initializer-list calls in intermediate classes are ignored when they're sub-objects.
- Specialty hammer. Most code never needs it.

### Object slicing (25.9)
- Copying a `Derived` into a `Base` (or pushing into a `vector<Base>`, or passing by value as `Base`) slices off the derived parts. The vptr in the copy points at `Base`'s vtable; polymorphism is gone.
- Hold polymorphic objects by pointer (`Base*`, `unique_ptr<Base>`), pass them by reference (`const Base&`).

### `dynamic_cast` (25.10)
- Type-checked downcast. `dynamic_cast<D*>(b)` returns `nullptr` on failure; `dynamic_cast<D&>(b)` throws `std::bad_cast`.
- Requires polymorphism (a virtual in the base). Has non-trivial runtime cost. Reach for a virtual function first; use `dynamic_cast` for the genuine "I need the derived type back" cases.

### Polymorphic `operator<<` (25.11)
- `operator<<` can't be virtual (it's a non-member). Pattern: one non-member `operator<<(out, const Base&)` that forwards to a `virtual print(out) const` member. Dispatch happens inside `print`.

## Quiz

### Q1 — six broken polymorphism programs

Each of these six programs is meant to output `"Derived"` (the derived class's `getName()`). Each has exactly one defect. Identify and fix the bug.

#### Q1a — reference vs. value

```cpp
class Base {
public:
    virtual const char* getName() const { return "Base"; }
};

class Derived : public Base {
public:
    const char* getName() const override { return "Derived"; }
};

int main() {
    Derived d{};
    Base b = d;                       // ← problem
    std::cout << b.getName() << '\n'; // prints "Base"
}
```

#### Q1b — const mismatch

```cpp
class Base {
public:
    virtual const char* getName() { return "Base"; }      // not const
};

class Derived : public Base {
public:
    const char* getName() const override { return "Derived"; } // const — fails to override
};
```

#### Q1c — slicing into a Base local

```cpp
Derived d{};
Base b{};
b = d;                       // assignment slices
std::cout << b.getName();    // "Base"
```

#### Q1d — final base

```cpp
class Base final { … };
class Derived : public Base { … }; // can't inherit from final class
```

#### Q1e — pure virtual with body in derived

```cpp
class Derived : public Base {
public:
    const char* getName() const override = 0 { return "Derived"; } // ill-formed
};
```

#### Q1f — deleting through a base without a virtual destructor

```cpp
class Base {
public:
    virtual const char* getName() const { return "Base"; }
    ~Base() {}      // not virtual
};

int main() {
    Base* p = new Derived{};
    std::cout << p->getName() << '\n';
    delete p;        // ~Derived never runs — UB
}
```

### Q2 — Shape hierarchy

Build a small polymorphic geometry hierarchy.

#### Q2a — `Shape` abstract base

Create an abstract `Shape` class:

- A pure virtual `print(std::ostream&) const` that returns `std::ostream&`.
- A non-member `operator<<(std::ostream&, const Shape&)` that forwards to `print`.
- A virtual destructor.

#### Q2b — `Triangle` and `Circle`

Use this `Point` helper:

```cpp
class Point {
private:
    int m_x{};
    int m_y{};
public:
    Point(int x, int y) : m_x{ x }, m_y{ y } {}
    friend std::ostream& operator<<(std::ostream& out, const Point& p) {
        return out << "Point(" << p.m_x << ", " << p.m_y << ')';
    }
};
```

Implement:

- `Triangle` — three `Point` members.
- `Circle` — one `Point` center and an integer radius.

Both override `print`. This `main` must produce the output shown.

```cpp
int main() {
    Circle c{ Point{ 1, 2 }, 7 };
    std::cout << c << '\n';

    Triangle t{ Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 } };
    std::cout << t << '\n';
}
```

Expected output:

```
Circle(Point(1, 2), radius 7)
Triangle(Point(1, 2), Point(3, 4), Point(5, 6))
```

#### Q2c — polymorphic container

Given:

```cpp
std::vector<Shape*> shapes;
shapes.push_back(new Circle{ Point{ 1, 2 }, 7 });
shapes.push_back(new Triangle{ Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 } });
shapes.push_back(new Circle{ Point{ 7, 8 }, 3 });
```

Write a `getLargestRadius(const std::vector<Shape*>&)` function that returns the largest radius across all `Circle`s in the vector (use `dynamic_cast`). Print every shape, then print the largest radius. Don't leak — `delete` every shape before returning from `main`.

Expected (order of shapes preserved):

```
Circle(Point(1, 2), radius 7)
Triangle(Point(1, 2), Point(3, 4), Point(5, 6))
Circle(Point(7, 8), radius 3)
The largest radius is: 7
```

#### Q2d — extra credit: `std::unique_ptr`

Rewrite Q2c using `std::vector<std::unique_ptr<Shape>>`. No raw `new`/`delete`; use `std::make_unique`. Adjust `getLargestRadius`'s parameter type accordingly.

## Run

    make 25.x

`quiz_solutions.cpp` has the worked code for Q1a–Q1f (six side-by-side mini-programs in named namespaces, each showing the fixed version) and Q2a–Q2d (Shape/Triangle/Circle, the raw-pointer version, and the `unique_ptr` version).
