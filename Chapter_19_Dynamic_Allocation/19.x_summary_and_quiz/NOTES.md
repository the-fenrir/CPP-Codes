# Chapter 19 — Summary & Quiz

> learncpp.com: chapter-summary/quiz page is currently 404 ("under construction"). What follows is a self-complete recap of the chapter material plus exercises that exercise every concept in 19.01–19.05.

## One-page recap

### `new` / `delete` (19.1)
- `new T{...}` returns `T*` to a heap object. `delete p` runs its destructor and frees the memory.
- Pair every `new` with exactly one `delete`. `delete nullptr` is a guaranteed no-op.
- After `delete p`, `p` is dangling. Set `p = nullptr` unless it's about to go out of scope.
- Failure modes to recognize on sight: leak (lost address), double-delete, use-after-free.
- `new (std::nothrow) T` returns `nullptr` on failure instead of throwing — but then *you* have to check.

### `new[]` / `delete[]` (19.2)
- `new T[n]` allocates `n` consecutive `T`s where `n` is a runtime value. `new T[n]{}` zero/value-initializes.
- **Must** be freed with `delete[]`, not `delete`. The runtime tracks the count behind the scenes.
- The pointer doesn't carry the length — you carry it yourself or use `std::vector`.
- No resize. Want resize? You wrote `std::vector` the hard way.

### Destructors and RAII (19.3)
- `~ClassName()` — no args, no return, exactly one per class. Runs automatically at end of lifetime.
- Triggers: stack object leaves scope; heap object is `delete`d; static/global at program exit.
- RAII = "every owned resource lives inside a class whose destructor releases it." Exception-safe by construction.
- **Rule of Three**: if your class needs a destructor, it almost certainly also needs a custom copy constructor and copy assignment (or to delete them). The default member-wise copy will alias the resource and double-delete.

### Pointers to pointers and dynamic 2D arrays (19.4)
- `T**` = pointer to pointer; `**pp` is the underlying `T`.
- Jagged 2D: `new T*[r]`, then per-row `new T[c]`. Free rows first, then the outer array.
- Rectangular 2D with constant column count: `new T[r][C]` returns a `T(*)[C]` — single allocation.
- Flat trick: one `new T[r*c]`, index as `row*c + col`. Fewer allocations, contiguous, easier to free.
- Three-star pointers exist; you don't want them.

### `void*` (19.5)
- A pointer that has erased its type. Holds any address; can't be dereferenced or arithmetic'd directly.
- `T*` → `void*` is implicit. `void*` → `T*` requires a cast and is on your conscience if `T` is wrong.
- "Null pointer" is a *value*; "void pointer" is a *type*. Orthogonal.
- Use in modern C++: read legacy/C APIs. Don't write it; use `std::variant`/`std::any`/templates.

### Modern-C++ replacements (the whole point of this chapter is to recognize these)
| Raw                                                       | Modern                                  |
|---|---|
| `T* p = new T(...); ... delete p;`                        | `auto p = std::make_unique<T>(...);`    |
| `T* a = new T[n]; ... delete[] a;`                        | `std::vector<T> a(n);`                  |
| `int** grid = new int*[r]; ... delete[] grid[i]; ...`     | `std::vector<std::vector<int>>` or flat `std::vector<int>` |
| `void* opaque; ... static_cast<T*>(opaque)`               | `std::variant<...>` + `std::visit`      |
| Manual destructor that `delete[]`s a member               | Don't write one — store `std::vector`   |

## Quiz

### Q1 — Spot the leak / dangle / double-delete

For each snippet, say what's wrong and how you'd fix it. Answers in `quiz_solutions.cpp` comments.

```cpp
// (a)
void a() {
    int* p = new int{ 1 };
    if (*p < 0) return;
    delete p;
}

// (b)
void b() {
    int* p = new int{ 1 };
    int* q = p;
    delete p;
    delete q;
}

// (c)
void c() {
    int* p = new int[10];
    delete p;
}

// (d)
void d() {
    int* p = new int{ 1 };
    p = new int{ 2 };
    delete p;
}
```

### Q2 — Sorted dynamic array of names

Write a program that:
1. has a hard-coded list of names (so it's runnable non-interactively),
2. allocates a `std::string` array of the right length with `new[]`,
3. fills it from that list,
4. sorts it with `std::sort`,
5. prints the sorted result,
6. cleans up with `delete[]`.

Then, in a comment, show the one-liner `std::vector` equivalent.

### Q3 — RAII `IntBuffer`

Write a class `IntBuffer` that owns an `int*` allocated with `new[]`. Requirements:

- constructor takes a size, allocates and zero-initializes,
- destructor releases with `delete[]`,
- `operator[]` for read/write,
- `size()` accessor,
- copies disabled (Rule of Three — implementing the copy correctly is chapter 22 territory; for now, delete it),
- a `main()` demonstrating that destruction is automatic on scope exit and on `delete`.

### Q4 — Flatten a 2D grid

Take a logical 4×5 grid of `int`. Allocate it as a single `new int[20]`. Provide a helper `at(row, col)` that maps to the flat index. Fill it with `row*10 + col`, print it as a 4×5 table, then `delete[]` it.

### Q5 — `void*` discussion (no code)

> What's the difference between a void pointer and a null pointer?

(This is the only quiz question on learncpp's 19.5 page.) Answer in your own words in NOTES, then check against the answer in `quiz_solutions.cpp`.

## Run

    make 19.x

`quiz_solutions.cpp` contains worked code for Q1–Q4 and the discussion answer for Q5 in comments.
