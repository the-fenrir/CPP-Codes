# Chapter 16 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-16-summary-and-quiz/

## One-page recap

### What a vector is (16.1–16.2)
- A **container** holds many values of one type; `std::vector<T>` is the workhorse container of the STL.
- **List constructor** (braces): `std::vector v{ 1, 2, 3 };` — three elements.
- **Length constructor** (parens): `std::vector<int> v(3);` — three zeros.
- **CTAD** (C++17) deduces `<T>` from the initializer.
- `const` is fine. `constexpr` is not (heap allocation).

### The unsigned saga (16.3, 16.6–16.7)
- `v.size()` is `std::size_t` (unsigned). Mixing with signed `int` produces warnings and the classic infinite reverse loop.
- Pick your fix per case: **range-for** if you don't need the index, **`std::ssize`** (C++20) for reverse loops with the index, **size_t** for forward loops, **cast at boundary** in mixed code.
- `.at(i)` is bounds-checked (`std::out_of_range`); useful while debugging, slower than `[i]`.

### Passing and returning (16.4–16.5)
- **Pass `const std::vector<T>&`** by default. **`std::vector<T>&`** to mutate. Don't pass by value — copies all elements.
- Use a **function template** when the element type varies.
- **Return by value**: NRVO usually elides the copy; otherwise the vector **moves** (steals its internal pointers in O(1)).
- Don't `return std::move(v);` — it disables NRVO.

### Loops and iteration (16.6, 16.8, 16.9)
- Index loop when you need *i*; **range-for** when you don't.
- `for (const auto& x : v)` is the default read-only traversal; `for (auto& x : v)` to mutate.
- **Enumerators as indices**: define an unscoped enum in a namespace with a `max_*` sentinel; assert the vector size against it.

### Capacity and stack behavior (16.10–16.11)
- **size** ≠ **capacity**. `size` = constructed elements; `capacity` = allocated slots.
- `reserve(n)` grows capacity (not size); `resize(n)` grows/shrinks size (capacity may grow).
- `push_back` amortized O(1) thanks to geometric growth; *any* push that reallocates **invalidates all pointers/refs/iterators**.
- Stack idiom: `push_back / back / pop_back`. Check `empty()` first — `pop_back` on empty is UB.

### vector&lt;bool&gt; (16.12)
- A bit-packing specialization, **not** a real `std::vector` of `bool`. `v[i]` returns a *proxy*, `&v[i]` doesn't give you `bool*`, `auto x = v[i];` doesn't give you a `bool`.
- For honest flags use `std::vector<char>` or `std::bitset<N>`.

## Quiz

### Q1 — vector definitions with CTAD

Write definitions for the following. Use CTAD where possible.

- **a)** A `std::vector` initialized with the first 6 even numbers.
- **b)** A constant `std::vector` initialized with the values `1.2`, `3.4`, `5.6`, and `7.8`.
- **c)** A constant `std::vector` of `std::string_view` initialized with the names `"Alex"`, `"Brad"`, `"Charles"`, and `"Dave"`.
- **d)** A `std::vector` with the single element value `12`.
- **e)** A `std::vector` with 12 int elements, initialized to the default values.

### Q2 — game inventory

**Step 1.** Define an unscoped enum in a namespace to identify item types (health potion, torch, arrow). Define a `std::vector` that stores how many of each item the player carries: 1 health potion, 5 torches, 10 arrows. Assert the vector has the correct number of initializers.

Expected output:

```
You have 16 total items
```

**Step 2.** Modify the program from step 1 to print the count and name of each item with correct pluralization. Use a loop.

Expected output:

```
You have 1 health potion
You have 5 torches
You have 10 arrows
You have 16 total items
```

### Q3 — min/max indices via `std::pair`

Write a function that takes a `std::vector` and returns a `std::pair` containing the indices of the elements with the min and max values in the vector. Test it on:

```cpp
std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };
```

Expected output:

```
With array ( 3, 8, 2, 5, 7, 8, 3 ):
The min element has index 2 and value 2
The max element has index 1 and value 8

With array ( 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 ):
The min element has index 4 and value 1.2
The max element has index 5 and value 8.8
```

### Q4 — user-entered numbers, then min/max

Modify the Q3 program to accept integers from the user until they enter `-1`, then display the vector and the min/max indices. Handle the case where `-1` is the first input reasonably (i.e., don't crash on an empty vector).

Expected output for input `3 8 5 2 3 7 -1`:

```
Enter numbers to add (use -1 to stop): 3 8 5 2 3 7 -1
With array ( 3, 8, 5, 2, 3, 7 ):
The min element has index 3 and value 2
The max element has index 1 and value 8
```

### Q5 — C++man (Hangman variant)

Implement a minimal Hangman variant called C++man. Four progressive steps; see learncpp.com for the full spec. Summary:

1. Define a namespace `WordList` containing: `"mystery"`, `"broccoli"`, `"account"`, `"almost"`, `"spaghetti"`, `"opinion"`, `"beautiful"`, `"distance"`, `"luggage"`. Randomly select one.
2. Build a `Session` class to hold the chosen word; display it as underscores; accept and validate single-letter input.
3. Track guessed letters with a `std::vector<bool>` indexed by `(letter % 32) - 1`. Reveal correctly-guessed letters in the underscored word; reject duplicate guesses. Run for 6 iterations to test.
4. Add win/loss: at most 6 wrong guesses (display them as `+` symbols counting *down*, with already-guessed wrong letters appended). Win when every letter is revealed; lose when wrong guesses are exhausted.

Final sample game state:

```
The word: ________   Wrong guesses: ++++++
Enter your next letter: a
No, 'a' is not in the word!

The word: ________   Wrong guesses: +++++a
...
The word: b__cc___   Wrong guesses: adefgh
You lost!  The word was: broccoli
```

`quiz_solutions.cpp` has full worked solutions for Q1–Q4 plus a complete C++man for Q5.

## Run

    make 16.x
