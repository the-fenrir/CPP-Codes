# 23.7 — `std::initializer_list`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdinitializer_list/

## Why it matters
Built-in arrays accept `int a[]{ 1, 2, 3 };` for free. The `IntArray` from 23.6 doesn't — you have to construct with a size and then assign element-by-element. `std::initializer_list<T>` is the language hook that lets *your* container also accept `IntArray a{ 1, 2, 3 };` directly. It's one of the few places where adding a constructor *changes the meaning* of existing call sites, so the gotchas matter as much as the feature itself.

## Key points
- `#include <initializer_list>`. The compiler synthesises an `std::initializer_list<T>` from a braced list and passes it to a matching constructor.
- Shape: `Foo(std::initializer_list<int> list)` — receive it as **a value**, by convention. It's a thin view (pointer + size); copying is cheap.
- Iterate with range-for, `.begin()/.end()`, or `std::copy`. Use `.size()` for the count.
- **Delegate** the list constructor through your size-only constructor to avoid duplicating allocation logic.
- Pair it with a list-taking `operator=` so `a = { 9, 8 };` works after construction. Without that, brace-assignment falls through to a temporary + copy-assignment combo that is, at minimum, wasteful.

## The trap: list constructor wins
`IntArray a{ 5 };` is *not* `IntArray(int)`. Once you've added an `initializer_list<int>` constructor, the braced form prefers the list version and produces an array `[5]` of size 1. To get the size-only constructor you must use parentheses: `IntArray a(5);`. The lesson stresses this is a **silent behaviour change** for any pre-existing code using brace init — read existing call sites before adding a list constructor.

## Code in this folder
- `main.cpp` — `IntArray` from 23.6 extended with `IntArray(std::initializer_list<int>)` and `operator=(std::initializer_list<int>)`. Demonstrates the brace-init trap by constructing both ways and showing which one wins.

## Gotchas
- `IntArray a{ 5 };` vs. `IntArray a(5);` — *not* equivalent once a list constructor exists. Pick parens for "n empty elements", braces for "exactly these elements".
- Narrowing in braced lists: `IntArray{ 1, 2.5 }` will not compile (good), but only because we constrained `T = int`. With templated containers, narrowing rules can bite differently.
- An `initializer_list` *does not own* its elements. They live in a backing array of static or automatic storage; copying the `initializer_list` doesn't copy the elements. Don't store the `initializer_list` itself as a member.

## Run
    make 23.07
