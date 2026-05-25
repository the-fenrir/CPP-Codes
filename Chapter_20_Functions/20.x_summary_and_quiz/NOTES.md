# Chapter 20 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-20-summary-and-quiz/

## One-page recap

### Function pointers (20.1)
- `ReturnType (*name)(ParamTypes...)` — the parentheses around `*name` are mandatory.
- A function name decays to its address; call through the pointer with `fn(args)`.
- Captureless lambdas convert to function pointers; capturing lambdas don't.
- For "store any callable with this signature," use `std::function<Ret(Args...)>`. For algorithmic hot paths, prefer a function-template parameter (inlinable).

### Stack & heap (20.2)
- Stack = automatic storage, fast, small, LIFO; frees on `}`.
- Heap = dynamic storage (`new`/`delete`, smart pointers), large, manual lifetime.
- Returning a pointer/reference to a local is UB. Huge stack arrays blow the stack at function entry.
- Modern default: `std::vector`, `std::string`, `std::unique_ptr` — heap payload, automatic cleanup.

### Recursion (20.3)
- Two parts: base case (reachable, doesn't recurse) and recursive case (strictly smaller input).
- Every level costs one stack frame; deep recursion overflows.
- Memoize when subproblems overlap (naive Fibonacci → exponential without it).
- Any recursion ⇄ iteration. Pick whichever mirrors the data better.

### Command line arguments (20.4)
- `int main(int argc, char* argv[])`. `argv[0]` is the program path; real args start at `argv[1]`.
- Everything arrives as a string — convert with `std::stoi`/`std::stod`/`std::from_chars` and handle failures.
- Quoting at the shell decides where one argument ends and the next begins.

### Ellipsis (20.5)
- `<cstdarg>` + `va_list`/`va_start`/`va_arg`/`va_end`. No type checking, no count checking.
- Default argument promotions apply: read `float` back as `double`, `char/short` as `int`.
- Avoid in new code: `std::initializer_list`, variadic templates, `std::format` cover the same ground safely.

### Lambdas (20.6)
- `[captures](params) -> Ret { body }`. Unique unnamed type; store with `auto` or `std::function`.
- Captureless ⇒ function-pointer convertible. `auto` parameters ⇒ generic lambda (templated `operator()`).
- Inline predicates next to the algorithm that uses them.

### Lambda captures (20.7)
- `[x]` value-capture (const, copied at construction), `[&x]` reference-capture (live, watch lifetimes), `[=]`/`[&]` implicit (avoid).
- `mutable` lets you mutate value captures — that mutation is local to the closure's copy.
- C++14 init capture `[name = expr]` enables move-capture (`[p = std::move(u)]`) and renames.
- `[this]` captures the pointer; `[*this]` (C++17) captures a copy — safer if the object may die first.

## Quiz

### Q1 — function prototypes

Write *prototypes* (no body needed) for each of these:

a) A function named `max()` that takes two doubles and returns the larger of the two.

b) A function named `swap()` that swaps two integers.

c) A function named `getLargestElement()` that takes a dynamically allocated array of integers and a length, and returns the largest element. The caller should be able to *modify* the value that's returned (i.e. you should be able to assign the return value).

### Q2 — what's wrong with each of these?

**a)**
```cpp
int& doSomething()
{
    int array[]{ 1, 2, 3, 4, 5 };
    return array[3];
}
```

**b)**
```cpp
int sumTo(int value)
{
    return value + sumTo(value - 1);
}
```

**c)**
```cpp
float divide(float x, float y)
{
    return x / y;
}

double divide(float x, float y)
{
    return x / y;
}
```

**d)**
```cpp
#include <iostream>

int main()
{
    int array[100000000]{};

    for (auto x: array)
        std::cout << x << ' ';

    std::cout << '\n';

    return 0;
}
```

**e)**
```cpp
#include <iostream>

int main(int argc, char* argv[])
{
    int age{ argv[1] };
    std::cout << "The user's age is " << age << '\n';

    return 0;
}
```

### Q3 — binary search

Binary search on a sorted array: look at the middle element; if it's the target, return its index; if it's larger than the target, recurse / iterate on the lower half; if smaller, on the upper half. Return `-1` if the target isn't found.

Write two versions of:

```cpp
int binarySearch(const int* array, int target, int min, int max);
```

where `min` and `max` are inclusive index bounds into `array`.

a) **Iterative** — loop until `min > max`.
b) **Recursive** — base case `min > max` returns `-1`; otherwise call yourself on the half that could still contain the target.

You can also use `std::binary_search` (returns bool) or `std::equal_range` (returns iterators) from `<algorithm>` in real code — but write the two versions yourself first.

## Answers (discussion)

### Q1 — answers

a) `double max(double a, double b);` — return by value; pass-by-value is fine for built-ins.

b) `void swap(int& a, int& b);` — references so changes propagate back. (Or use `std::swap`; in real code you would.)

c) `int& getLargestElement(int* array, int length);` — return a *reference* so the caller can assign through it (e.g. `getLargestElement(arr, n) = 0;`). Note: returning a reference to a heap element is fine while the caller keeps the buffer alive.

### Q2 — answers

**a)** Returns a reference to a local array's element. The array's storage dies at `}`, so the caller gets a dangling reference. Returning by value (or making `array` `static`, though that's its own design smell) fixes it.

**b)** Has no base case — `sumTo(0)` keeps calling `sumTo(-1)`, `sumTo(-2)`, … forever. Add `if (value <= 0) return 0;` (or `<= 1`, depending on intent) before the recursive call.

**c)** Two overloads with identical parameter types differing only in return type. C++ doesn't allow overload resolution on return type, so this is a compile error at *declaration* time. Pick one; if both are needed, rename or templatize.

**d)** `int array[100'000'000]{};` — that's ~400 MB on the stack. The default stack is ~1 MB on Windows, ~8 MB on Linux. The program crashes (stack overflow) at function entry before any code runs. Put big buffers on the heap: `std::vector<int> array(100'000'000);`.

**e)** `argv[1]` is a `char*` (a C string), not an integer. `int age{ argv[1] };` doesn't compile, and `int age = argv[1];` would just be the pointer-to-int conversion error. Convert explicitly: `int age = std::stoi(argv[1]);` — and also check that `argc >= 2` first, plus handle `std::invalid_argument`/`std::out_of_range`.

### Q3 — answers

See `quiz_solutions.cpp`. Both versions have the same shape: compute `mid = min + (max - min) / 2` (the `(max - min) / 2` form avoids overflow you'd get from `(min + max) / 2` on large arrays), compare to target, recurse / loop on the matching half. Base/termination is `min > max` ⇒ not found, return `-1`.

## Run

    make 20.x

`quiz_solutions.cpp` has worked answers for Q1 (signatures + tiny demos), Q2 (commentary), and Q3 (iterative + recursive binary search).
