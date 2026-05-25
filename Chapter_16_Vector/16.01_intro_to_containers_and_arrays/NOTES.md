# 16.1 — Introduction to containers and arrays

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-containers-and-arrays/

## Why it matters
Up to here you've held one value per variable. The moment you need "all the test scores" or "every enemy on screen," you need a **container** — a type whose job is to hold many values of one type. Arrays are the oldest container in the family; everything else in the STL builds on the same vocabulary.

## Key points
- **Container**: a data type whose purpose is to hold a collection of values, with operations to add, remove, count, and iterate.
- **Container class**: a class implementing that abstraction (`std::vector`, `std::array`, `std::string`, `std::list`, …).
- **Array**: a container of values laid out contiguously in memory, accessed by an integer **index** in `[0, length)`.
- **Length** = current number of elements. Distinct from physical storage size.
- Element types must be homogeneous — an array of `int` holds only `int`. (Mixed-type → use a struct/tuple.)
- C++ arrays you'll meet in this chapter and the next: `std::vector` (dynamic length), `std::array` (fixed length known at compile time), C-style arrays (legacy).
- This chapter focuses on `std::vector` because it's the one you reach for by default.

## Code in this folder
- `main.cpp` — minimal "container vs. one variable" demo with a `std::vector<int>`.

## Gotchas
- "Array" in everyday speech and "array" in C++ aren't quite the same — C++ has multiple array-like types. When the docs say "array," they mean the abstract concept.
- Indices are **0-based** and stop at `length - 1`. The last element is at `v[v.size() - 1]`, not `v[v.size()]`.

## Run
    make 16.01
