# Chapter 17 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-17-summary-and-quiz/

## One-page recap

### `std::array<T, N>` (17.1–17.6)
- Same memory layout as a C-style array, but a value type: knows its size, copyable, returnable, no decay.
- Size and type are both template parameters; both must be constant expressions.
- `a.size()` / `std::size(a)` — unsigned. `std::ssize(a)` — signed (C++20).
- Index with `a[i]` (unchecked, fast), `a.at(i)` (throws), or `std::get<I>(a)` (compile-time checked).
- Pass by `const std::array<T, N>&` (templated on `N` when size varies) or by `std::span`.
- Returning by value is free thanks to mandatory copy elision (C++17).
- Initializing `std::array` of class types: strict form needs **double outer braces**; brace elision usually lets you drop them.
- `std::reference_wrapper` is the workaround for "array of references."
- Pair a `std::array` with an *unscoped* enum + `max_X` sentinel for compile-time-checked parallel data tables.

### C-style arrays (17.7–17.12)
- `int arr[N];` — fixed size, no length stored in the type, value-init only with `{}`.
- **Decay**: the name converts to a pointer at the slightest provocation. After decay you lose `sizeof(arr)`, `std::size(arr)`, range-`for`.
- `void f(int arr[5])` is silently rewritten to `void f(int*)`. The `[5]` is documentation only.
- Workarounds: reference-to-array (`int (&)[N]`), template-on-`N`, or just use `std::array` / `std::span`.
- `arr[i]` is sugar for `*(arr + i)`. Pointer arithmetic steps by `sizeof(T)`, not bytes.
- C-style strings are `char[]` terminated by `\0`. `std::strlen` is O(n) and excludes the terminator; `sizeof` is compile-time and includes it.
- Prefer `constexpr std::string_view` over `const char[]` / `const char*` for string constants.
- Multidimensional C-style arrays: row-major, can omit *only* the outer dimension. `int g[][3]` ok, `int g[][]` not.

### Multidimensional `std::array` (17.13)
- Spelled `std::array<std::array<T, Cols>, Rows>`. No special syntax — just nest.
- A `using` alias is mandatory for sanity. Each row is a real value, no decay.
- Memory layout is still row-major contiguous.

### When to use what
- **Compile-time known size**: `std::array`.
- **Runtime size**: `std::vector` (chapter 16).
- **View over either, plus C-style arrays**: `std::span` (C++20).
- **C-style array**: only when you must (legacy code, C API).

## Quiz

### Q1 — Spot the bug (three snippets)

#### Q1a
```cpp
#include <array>
#include <iostream>

int main()
{
    std::array arr { 0, 1, 2, 3 };

    for (std::size_t count{ 0 }; count <= std::size(arr); ++count)
        std::cout << arr[count] << ' ';

    std::cout << '\n';
}
```
**Bug.** Off-by-one. `count <= std::size(arr)` runs through `count == 4`, but valid indices are `0..3`. Reading `arr[4]` is UB.
**Fix.** Change `<=` to `<`.

#### Q1b
```cpp
#include <iostream>

void printArray(int array[])
{
    for (int element : array)   // ← won't compile
        std::cout << element << ' ';
}

int main()
{
    int array[] { 9, 7, 5, 3, 1 };
    printArray(array);
}
```
**Bug.** `int array[]` as a function parameter is just `int*` — the array has decayed. A range-`for` needs a *type* with `begin()`/`end()`, which a bare pointer doesn't have.
**Fix.** Take a `std::array<int, N>` (template the function on `N`) or a `std::span<int>`. Easiest mirror of intent here: declare `arr` as `std::array` and pass it.

#### Q1c
```cpp
int main()
{
    std::size_t length{};
    std::cin >> length;
    std::array<int, length> scores;   // ← won't compile
}
```
**Bug.** The size template argument to `std::array` must be a constant expression. `length` is a runtime variable.
**Fix.** Use `std::vector<int> scores(length);` instead.

### Q2 — Roscoe's Potion Emporium

Build a shopping loop:
- A `Potion` namespace with an unscoped enum (`healing, mana, speed, invisibility, max_potions`) and three `constexpr std::array`s: `name` (string_view), `cost` (int), and we'll skip "types" (the learncpp version of this array adds nothing).
- A `shop()` free function that prints the menu.
- A `Player` class holding `m_name`, `m_gold`, and `m_inventory` (a `std::array<int, max_potions>` counting how many of each potion the player owns).
- A purchase loop that prompts for a potion number or `'q'`, handles invalid input cleanly (`std::cin.clear()` + ignore on parse failure), debits gold, increments inventory.
- On quit: print inventory summary and remaining gold.

We pin the RNG to a fixed seed in `quiz_solutions.cpp` so the output is reproducible. Real code would use a `std::random_device`-seeded generator.

### Q3 — Card foundation

Build the data layer for a 52-card deck:
- Enums `Rank { ace, two, …, king, max_ranks }` and `Suit { clubs, diamonds, hearts, spades, max_suits }`.
- A `Card` struct holding a `Rank` and a `Suit`. Overload `operator<<` to print "AS", "TD", etc. (T = ten).
- Static `constexpr std::array allRanks` and `allSuits` for iteration.
- A `Deck` class wrapping `std::array<Card, 52>`, with `dealCard()` (pops from a front index) and `shuffle()` (`std::shuffle` with a Mersenne Twister).

The interesting design point: deck order is *just* the order of the underlying array; "dealing" is a moving index, not an `erase()`. That keeps the storage `std::array`-shaped.

### Q4 — Blackjack

Same `Deck` from Q3, plus game loop:
- Player and dealer hands as `std::vector<Card>` (size varies — you draw until you stand or bust).
- Score with aces hard-coded as 11 for now; bust = score > 21.
- Player turns first (hit/stand loop), then dealer (auto-hit while score < 17), then compare.

The lesson here is *which* container to use. The deck is `std::array` (always 52). The hands are `std::vector` (size unknown until play).

### Q5 — Discussion: flexible aces and ties

**Discussion question.** How would you handle aces that count as either 1 or 11, and how should the game treat a tie?

**Answer.** For aces: count aces as 11 by default, then while the total exceeds 21 and you have an ace, *demote* one ace from 11 to 1 (subtract 10). Done greedily it's optimal — you only demote when needed, so you end up with the highest score that doesn't bust. Implementation: track ace count in the hand, compute base score with all aces at 11, then `while (score > 21 && aces > 0) { score -= 10; --aces; }`.

For ties: a tie ("push") returns the wager and ends the hand — neither side wins. The simplest representation: a 3-state result enum (`player_wins, dealer_wins, push`). Most real blackjack variants treat dealer-22 (bust) with a player-21 as a player win, not a push — encode rules explicitly rather than relying on "whoever had more."

## Run

    make 17.x

`quiz_solutions.cpp` contains:
- `q1a()`, `q1b()`, `q1c()` — fixed versions of each Q1 snippet, each in its own scope.
- `q2()` — Roscoe's potion emporium, with input scripted via a `std::stringstream` so the build is non-interactive.
- `q3_q4()` — card deck + a one-round blackjack mini-game with flexible aces (Q5).

The discussion-only answers live in this NOTES.md.
