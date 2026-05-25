# Chapter 18 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/ (Chapter 18 is marked "under construction" on learncpp; there is no official summary/quiz page. The quiz below is a synthesis covering the chapter's material.)

## One-page recap

### Selection sort (18.1)
- Outer loop walks index `i`; inner loop finds the smallest in `[i+1, n)`; swap it into position `i`. O(n²).
- `std::swap` (from `<utility>`) exchanges two values without a manual temp.
- For real code, use `std::sort` from `<algorithm>` — typically O(n log n) introsort, in-place.

### Iterators (18.2)
- An iterator is an abstract pointer over a container's elements. Four core operations: `*it`, `++it`, `==`/`!=`, copy.
- Containers expose `begin()` / `end()`; the range is **half-open** `[begin, end)`. `end()` is a sentinel — dereferencing it is UB.
- Range-based `for` is sugar over `begin()`/`end()` + `++`/`*`.
- `const_iterator` (`cbegin()`/`cend()`) is the read-only form.
- **Iterator invalidation** — mutating a container can dangle existing iterators. Re-fetch after modifying.

### Standard library algorithms (18.3)
- `<algorithm>` is organized as inspectors (`find`, `count`, `all_of`), mutators (`sort`, `reverse`, `fill`), facilitators (`for_each`, `transform`).
- Common shape: `algo(first, last, ...)`. Predicates and comparators are anything callable — most commonly **lambdas**: `[](int x){ return x % 2 == 0; }`.
- `std::find(...)` returns `end()` when not found — check before dereferencing.
- `std::sort` needs random-access iterators (`vector`, `array`, `deque`, raw arrays). `std::list` has its own member `sort()`.
- C++20 `std::ranges::sort(v)` drops the `.begin()/.end()` boilerplate.
- Erase-remove idiom: `v.erase(std::remove_if(v.begin(), v.end(), pred), v.end());` — or C++20's `std::erase_if(v, pred)`.

### Timing (18.4)
- Use `std::chrono::steady_clock`: monotonic, immune to wall-clock adjustments.
- Pattern: snapshot `now()` before and after, subtract, cast to `duration<double>` for seconds.
- A `Timer` class (start in ctor, `elapsed()` member) makes "time this block" a one-liner.
- Always benchmark with optimizations on (`-O2`/`-O3`). Compare *ratios*, not absolute numbers — they don't port.
- Beware optimizer eliminating unused results; print or store them.

## Quiz

### Q1 — Rewrite selection sort using iterators

Selection sort in 18.1 was written with `int` indices. Rewrite it as a function template that takes two random-access iterators `first` and `last` and sorts the half-open range `[first, last)`. Use `std::iter_swap` and `std::min_element` from `<algorithm>`. Then sort a `std::vector<int>{ 5, 1, 4, 2, 8, 3 }` with it and print the result.

Hints:
- `std::min_element(a, b)` returns an iterator to the smallest element in `[a, b)`.
- `std::iter_swap(x, y)` swaps the values two iterators point to.
- The outer loop's loop variable is an iterator, not an index — compare with `!=`, advance with `++`.

### Q2 — Find first negative and remove all evens

Given `std::vector<int> v{ 3, -2, 7, -4, 8, 1, 6 }`:

(a) Use `std::find_if` with a lambda to find the **first negative** element. Print its value if found, or "none" if not.

(b) Use the **erase-remove idiom** (or C++20 `std::erase_if`) to remove every even element from `v`, then print the survivors.

Expected output:
```
first negative: -2
survivors: 3 7 1
```

### Q3 — Discussion: why is `end()` one past the last element?

Why does the standard library make `end()` a one-past-the-end sentinel instead of pointing at the last valid element? Give two concrete consequences of this choice.

### Q4 — Time `std::sort` vs. `std::stable_sort`

Using the `Timer` class from 18.4, generate a `std::vector<int>` of `N = 50'000` shuffled values (use `std::mt19937` with a fixed seed for reproducibility). Time `std::sort` and `std::stable_sort` on a fresh copy of the same input. Print both timings and the ratio.

You don't need to predict which is faster — just measure. The point of the exercise is the *pattern*: same input, fresh copy each time, fixed seed, ratio not absolute.

## Answers

### Q1 — solution

See `quiz_solutions.cpp`. Key shape:
```cpp
template <typename It>
void selectionSort(It first, It last) {
    for (auto i = first; i != last; ++i) {
        auto smallest = std::min_element(i, last);
        std::iter_swap(i, smallest);
    }
}
```
This is now generic: works on `std::vector<int>::iterator`, raw pointers, `std::array<int, N>::iterator` — anything random-access (or forward-iterable, really; `std::min_element` only needs forward).

### Q2 — solution

See `quiz_solutions.cpp`. (a) is one `std::find_if` call; (b) is one line — either:
```cpp
v.erase(std::remove_if(v.begin(), v.end(),
                       [](int x){ return x % 2 == 0; }),
        v.end());
```
or C++20:
```cpp
std::erase_if(v, [](int x){ return x % 2 == 0; });
```

### Q3 — discussion

A one-past-the-end sentinel makes two things clean:

1. **Empty ranges are expressible**. If `end()` were "the last element," an empty container would have no valid `end()`. With one-past-the-end, an empty container has `begin() == end()`, and every algorithm's loop body `while (it != end)` correctly does zero iterations.
2. **Range length is `end - begin`** for random-access iterators — no off-by-one. A loop `for (auto it = first; it != last; ++it)` covers exactly the elements you want, and the half-open range `[first, last)` composes cleanly: split into `[first, mid)` and `[mid, last)` with no overlap and no gap.

(Bonus: "not found" return values from `std::find`-family algorithms can use the same `end()` sentinel — there's no valid element to confuse it with.)

### Q4 — solution

See `quiz_solutions.cpp`. The output will vary by machine and build flags; the *pattern* is what matters:

- both sorts get a fresh copy of the same shuffled vector;
- `Timer` is reset between runs;
- ratio is printed rather than just absolute seconds.

For `int` keys with no equivalent elements, `std::sort` is usually a hair faster (no stability guarantee to maintain). For larger/expensive-to-move element types the gap can grow.

## Run

    make 18.x

`quiz_solutions.cpp` has worked code for Q1, Q2, and Q4 with commentary; Q3 is discussion-only in this file.
