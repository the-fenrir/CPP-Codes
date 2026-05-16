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

## Quiz — Random Monster Generator

One multi-part exercise. Each step builds on the previous one — recommended to attempt them in order before peeking at the solution.

### Part a — `MonsterType` scoped enum

Define a scoped enumeration named `MonsterType` outside any class, with the following enumerators:

```
Dragon, Goblin, Ogre, Orc, Skeleton, Troll, Vampire, Zombie
```

Add a final enumerator `maxMonsterTypes` whose value equals the count of real types (useful for picking one at random later).

### Part b — `Monster` class skeleton

Create a `Monster` class with four **private** member variables:

| Member       | Type            |
|--------------|-----------------|
| type         | `MonsterType`   |
| name         | `std::string`   |
| roar         | `std::string`   |
| hit points   | `int`           |

Just the fields for now — no constructor yet.

### Part c — nest the enum inside `Monster`

Move the `MonsterType` enum *inside* the `Monster` class as a **nested** type. Rename it to `Type`. Make it **unscoped** (`enum`, not `enum class`).

This means callers refer to a monster type as `Monster::Skeleton` rather than `MonsterType::Skeleton`. (Unscoped + nested gives you class-qualified naming without the extra `Type::` prefix.) Update the type member's declared type from `MonsterType` to `Type`.

### Part d — constructor

Add a constructor accepting `(type, name, roar, hit points)`. After this part, this line must compile:

```cpp
Monster skeleton{ Monster::Skeleton, "Bones", "*rattle*", 4 };
```

### Part e — `getTypeString()` and `print()`

Add a `getTypeString()` member function returning the type as a string (`"dragon"`, `"goblin"`, …).

Add a `print()` member function. For a live monster (hit points > 0):

```
Bones the skeleton has 4 hit points and says *rattle*.
```

For a dead monster (hit points ≤ 0):

```
Nibblez the vampire is dead.
```

### Part f — `MonsterGenerator` namespace

Create a `MonsterGenerator` namespace with one function:

```cpp
Monster generate();
```

For now, have `generate()` simply return the skeleton example from part d.

### Part g — name / roar helpers

Inside the `MonsterGenerator` namespace, add two helpers:

```cpp
std::string getName(int n);   // n in [0, 5] — returns "Blarg" / "Moog" / etc.
std::string getRoar(int n);   // n in [0, 5] — returns "*ROAR*" / "*hiss*" / etc.
```

Update `generate()` to call these helpers (still with hard-coded indices for now — randomness comes in the next part).

### Part h — randomness

Wire up randomness:

- Random `Type` from `[0, maxMonsterTypes)`.
- Random name index `[0, 5]`.
- Random roar index `[0, 5]`.
- Random hit points in `[1, 100]`.

> The site uses a `Random.h` header introduced in lesson 8.15. To keep this folder standalone, we use `<random>` directly — same idea, just inline. See `quiz_solutions.cpp` for the helper.

### Expected behavior

A few example runs should produce monsters like:

```
Mort the troll has 28 hit points and says *snarl*.
Tyrn the zombie has 14 hit points and says *moan*.
Blarg the goblin has 86 hit points and says *hiss*.
```

If you force a hit-points value of 0 (or below), `print()` should emit the dead-monster form instead — the solution forces one such case in `main()` to exercise both branches.

## Run

    make 15.x

`quiz_solutions.cpp` has the worked code, with `// ── a) ──` … `// ── h) ──` markers tying each block back to its problem part.
