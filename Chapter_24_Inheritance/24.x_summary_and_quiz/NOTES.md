# Chapter 24 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-24-summary-and-quiz/

## One-page recap

### Inheritance basics (24.1–24.2)
- Inheritance models **is-a**. Composition models has-a. Pick the relationship first, the mechanism follows.
- `class Derived : public Base {}`. The derived object physically contains a base subobject.
- Inherited: data members and member functions. **Not inherited**: constructors, destructor, assignment operator, friends.

### Construction order (24.3–24.4)
- Construction: **base first**, then derived (members in declaration order). Destruction reverses.
- Multi-level: `A → B → C` → ctor order `A, B, C`; dtor order `~C, ~B, ~A`.
- Multiple objects in one scope: each fully constructed in order, then destroyed in reverse order at scope exit.
- Forward base ctor args via the initializer list: `Derived(...) : Base{ ... }, m_x{...} {}`. Omit the base entry and the compiler calls `Base{}` — error if the base has no usable default.

### Access (24.5)
- Member access: `public` (everyone) / `protected` (class + derived) / `private` (class only).
- Inheritance mode caps inherited access. Memorize:
  | base member  | `: public` | `: protected` | `: private` |
  |---|---|---|---|
  | `public`     | `public`    | `protected` | `private` |
  | `protected`  | `protected` | `protected` | `private` |
  | `private`    | inaccessible | inaccessible | inaccessible |
- Default: `public` inheritance. `protected`/`private` inheritance is "implemented-in-terms-of" — composition usually says it better.

### Adding, overriding, hiding (24.6–24.8)
- **Add** new members on the derived side when only some derivatives need them. Don't push them into the base.
- **Override** (non-virtual): redeclare in derived. To extend rather than replace, call `Base::fn()` from the derived version — never a bare `fn()` (infinite recursion).
- **Hide**:
  - `using Base::fn;` under a different access label changes the access of that inherited member in the derived class.
  - Redeclaring `fn() = delete;` in derived blocks calls through the derived type.
  - Defining *any* `fn` in derived hides the **whole overload set** of `fn` from the base. Restore the rest with `using Base::fn;`.

### Multiple inheritance (24.9)
- `class C : public A, public B {};` is legal. Ambiguity on same-named members → qualify (`A::fn`).
- Diamond (`B`,`C` both inherit `A`, `D : B, C`) yields two `A` subobjects. `virtual` inheritance collapses them — uncommon, expensive, save it for library code.
- Default to: single concrete base for state + zero or more abstract bases for interfaces.

## Quiz

### Q1 — Determine the output

For each snippet below, predict the output (or "does not compile" with the reason). All snippets reuse the same trace-on-construct/destruct pattern.

**Q1a** — One derived object, single inheritance:
```cpp
class Base    { public: Base()    { std::cout << "Base()\n"; }    ~Base()    { std::cout << "~Base()\n"; } };
class Derived : public Base {
public: Derived() { std::cout << "Derived()\n"; } ~Derived() { std::cout << "~Derived()\n"; }
};
int main() { Derived d; }
```
Expected:
```
Base()
Derived()
~Derived()
~Base()
```

**Q1b** — Two objects in the same scope, defined Derived then Base:
```cpp
int main() { Derived d; Base b; }
```
Expected:
```
Base()
Derived()
Base()
~Base()
~Derived()
~Base()
```
Local variables are destroyed in **reverse** order of definition; within each object, derived runs before base.

**Q1c** — Base has a `private` member `m_x`; `Derived::print()` tries to read it. Result: **does not compile**. `m_x` is private to `Base`; even though it lives inside every `Derived` object, `Derived` cannot name it.

**Q1d** — Change `m_x` to `protected`; everything else the same. Expected:
```
Base()
Derived()
Derived: 5
~Derived()
~Base()
```
`protected` is exactly the access level intended for derived-class consumption.

**Q1e** — Three-level hierarchy: `D2 : public Derived : public Base`. `D2` has no `print()` override. Calling `print()` on a `D2` resolves to `Derived::print()` (next visible by name lookup). Expected:
```
Base()
Derived()
D2()
Derived: 5
~D2()
~Derived()
~Base()
```

### Q2a — Fruit / Apple / Banana

Design `Fruit` (members: `name`, `color`, both `const`-able). Derive `Apple` (defaults to red) and `Banana` (defaults to yellow). The main program prints "My apple is red." and "My banana is yellow."

### Q2b — Add `GrannySmith`

Derive `GrannySmith` from `Apple`; sets name to `"granny smith apple"` and color to `"green"`. Output adds: "My granny smith apple is green."

### Q3 — Mini game: Creature / Player / Monster

Build a turn-based encounter game. Spec lifted from the lesson:

- **Q3a** `Creature` (base): members `name`, `symbol`, `health`, `damage`, `gold`; accessors; `reduceHealth(int)`; `isDead()`; `addGold(int)`.
- **Q3b** `Player : public Creature`: adds `m_level{1}`; `levelUp()` increments level and damage; `hasWon()` true at level 20.
- **Q3c** `Monster : public Creature`: enum `Type { dragon, orc, slime, max_types }`.
- **Q3d** `Monster(Type)` constructor uses a `static inline` lookup table of `Creature` defaults.
- **Q3e** `static Monster getRandomMonster()` using a small RNG helper.
- **Q3f** Game loop: random encounter → `(R)un` (50/50; failure → free monster hit) or `(F)ight` (player hits first; if monster dies, level up and take gold; else monster counter-attacks). End on player death or level 20.

The complete game would dwarf this folder's purpose; `quiz_solutions.cpp` implements Q1 verification, Q2a, Q2b, and Q3a–Q3c (the structural pieces). The full Q3 game is identical in structure once you've understood the inheritance choices made here.

## Run

    make 24.x

`quiz_solutions.cpp` contains worked solutions with inline commentary explaining each design choice.
