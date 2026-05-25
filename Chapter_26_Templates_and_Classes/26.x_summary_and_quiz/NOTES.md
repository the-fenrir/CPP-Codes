# Chapter 26 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-26-summary-and-quiz/

## One-page recap

### Template classes (26.1)
- `template <typename T> class Foo { … };`. Each instantiation is a distinct type.
- Out-of-line definitions repeat the template header and qualify the class: `template <typename T> T& Foo<T>::bar() { … }`.
- Templates instantiate per use site → bodies must be visible there → put the whole template in the header (or `.inl` included from the header, or use explicit instantiation).

### Non-type template parameters (26.2)
- Compile-time *values* as template arguments: `template <typename T, std::size_t N>`.
- Argument must be a constant expression. Carrying size in the type ⇒ stack allocation, `static_assert`-able shape, no implicit conversion between different `N`s.
- Used pervasively in the standard library (`std::array<T, N>`).

### Function template specialization (26.3)
- `template<> void print<double>(const double&) { … }` — empty `<>`, the type in `<>` after the name.
- Not implicitly inline; if put in a header, mark `inline`.
- A plain overload usually beats a specialization both in flexibility and in overload resolution — *prefer overloads*.
- Function templates **cannot be partially specialized**. Write another overload.

### Class template specialization (26.4)
- `template<> class Storage8<bool> { … };` — a fully independent class. Different storage, different members, same public interface by convention.
- You can also specialize a single member function: `template<> void Storage<double>::print() { … }`.
- Define specializations in the same header as the primary so every TU sees them.

### Partial template specialization (26.5)
- Pin some parameters, leave others free: `template <int N> class StaticArray<char, N> { … };`.
- Works on shape too: `Foo<T*>`, `Foo<T, T>`, `Foo<std::vector<T>>`. The compiler picks the *most specialized* match.
- Functions still can't be partially specialized — that's the boundary line.

### Partial specialization for pointers (26.6)
- `template <typename T> class Storage<T*> { … };`. Inside, `T` is the pointee.
- The primary owns a copy, the pointer specialization (by default) is a view. That ownership asymmetry is the real lesson — decide explicitly: document as a view, forbid pointers with `static_assert`, or deep-copy via `std::unique_ptr`.

## Quiz

### Q1 — `Pair1<T>`: both members same type

Write a class template `Pair1<T>` where both stored values share one type parameter. Provide `first()` and `second()` const accessors. This program must compile and produce the expected output:

```cpp
int main()
{
    Pair1<int> p1 { 5, 8 };
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2 { 2.3, 4.5 };
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
}
```

Expected output:

```
Pair: 5 8
Pair: 2.3 4.5
```

### Q2 — `Pair<T, U>`: two type parameters

Now generalize: a class template `Pair<T, U>` taking two type parameters, one per element. Same `first()` / `second()` accessors.

```cpp
int main()
{
    Pair<int, double> p1 { 5, 6.7 };
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair<double, int> p2 { 2.3, 4 };
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
}
```

Expected output:

```
Pair: 5 6.7
Pair: 2.3 4
```

### Q3 — `StringValuePair<T>` via partial specialization

Write a class template `StringValuePair<T>` that **inherits from a partial specialization** of `Pair<T, U>` where the first type is fixed to `std::string` and the second is left free.

```cpp
int main()
{
    StringValuePair<int> svp { "Hello", 5 };
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
}
```

Expected output:

```
Pair: Hello 5
```

The point of the exercise: practice the partial-specialization syntax (`Pair<std::string, T>`), and use inheritance to give that specialization a nicer name (`StringValuePair<T>`) without re-implementing the storage.

## Run

    make 26.x

`quiz_solutions.cpp` has the worked code for Q1, Q2, and Q3, with inline commentary on each design choice.
