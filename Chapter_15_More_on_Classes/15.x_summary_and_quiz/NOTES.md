# Chapter 15 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-15-summary-and-quiz/

## One-page recap

### The hidden `this` (15.1)
- Every non-static member function gets `this` — a `Foo*` (or `const Foo*`) to the called object.
- Return `*this` (return type `Foo&`) from setters to enable chaining: `obj.setA(1).setB(2)`.

### Headers and source (15.2)
- Declarations in `.h`, definitions in `.cpp`. `#pragma once` on every header.
- Member functions defined inside the class are implicitly `inline`.
- **Templates live entirely in headers** — they instantiate per use site.

### Nested types (15.3)
- Nested classes, enums, and type aliases live in the outer class's scope and respect access specifiers.
- Use private nested types for implementation details (`LinkedList::Node`), public ones for visible API (`Container::value_type`, `Door::State`).

### Destructors and RAII (15.4)
- `~Foo()` runs automatically when the object dies; in **reverse declaration order** for members.
- RAII = constructor acquires, destructor releases. The engine of all C++ resource safety.
- Rule of 0/3/5: design so you need zero. If you need one of `(dtor, copy, copy-assign[, move, move-assign])`, you probably need them all.
- Destructors must not throw.

### Class templates (15.5)
- `template <typename T> class Foo { … };`. Each `Foo<X>` is a distinct type.
- Out-of-line member function: repeat the template header. `template <typename T> void Foo<T>::bar() {}`.
- Entire definition must be visible to callers → keep templates in headers.
- CTAD (C++17) deduces template args from constructor args: `Pair p{ 1, 2.5 };`.

### Static members (15.6–15.7)
- Static **variable**: one copy shared across all instances. `inline static` (C++17) lets you init in-class.
- Static **function**: no `this`; can only access static members. Called as `Class::func()`.
- Static is per-class; namespaces are per-... namespace. Pick by intent.

### Friends (15.8–15.9)
- `friend` grants a non-member function or another class access to your privates.
- Use sparingly — most useful for `operator<<` and tightly-coupled helpers.
- Friendship is one-directional, non-transitive, and granted by the holder of secrets.

### Ref qualifiers (15.10)
- `void method() &;` callable only on lvalues; `void method() &&;` only on rvalues.
- Lets a getter return a ref to internals on lvalues, but return by value (moving out) on temporaries — eliminating the dangling-reference footgun from 14.7.

## Quiz

Chapter 15's quiz is a single multi-part exercise: a random monster generator that exercises nested types, constructors, static members, and namespace-style utilities.

See `quiz_solutions.cpp` for the worked solution.

## Run

    make 15.x
