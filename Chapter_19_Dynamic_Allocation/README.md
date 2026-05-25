# Chapter 19 — Dynamic Allocation

Chapter 19 covers raw dynamic memory: `new`/`delete`, dynamic arrays with `new[]`/`delete[]`, destructors that clean up resources (RAII), pointers to pointers and dynamic multidimensional arrays, and `void*`. The lessons use raw owning pointers on purpose — once you've felt the failure modes, you'll appreciate why every modern example reaches for `std::unique_ptr` and `std::vector` instead.

> learncpp's chapter is marked "under construction" and has no published chapter-summary/quiz page yet. The summary folder below synthesizes one from the lesson material so the chapter is self-complete.

## Lessons

| # | Lesson |
|---|---|
| 19.01 | [Dynamic memory allocation with `new` and `delete`](19.01_new_and_delete/NOTES.md) |
| 19.02 | [Dynamically allocating arrays](19.02_dynamic_arrays/NOTES.md) |
| 19.03 | [Destructors](19.03_destructors/NOTES.md) |
| 19.04 | [Pointers to pointers and dynamic multidimensional arrays](19.04_pointers_to_pointers/NOTES.md) |
| 19.05 | [Void pointers](19.05_void_pointers/NOTES.md) |
| 19.x | [Summary & quiz](19.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear. The chapter is short but mostly about failure modes, so read every "Gotchas" section before writing your own variant.

- **19.01 → 19.02** — single-object `new`/`delete` first, then arrays. The single most common bug in this chapter is mixing `delete` and `delete[]`.
- **19.03** — destructors only really click once you've leaked memory yourself in 19.01/19.02. RAII is the *answer* to those leaks; that framing matters.
- **19.04** — pointers-to-pointers are mostly read-only knowledge. The "flatten 2D into 1D" trick at the end is the takeaway.
- **19.05** — `void*` is the chapter's "here be dragons" section: useful to recognize in legacy C APIs, almost never useful to write.

## Modern alternative (read this once, then apply throughout)

Every example in this chapter has a safer modern equivalent. Internalize the mapping:

| Raw | Modern (preferred) |
|---|---|
| `T* p = new T{...}; ... delete p;` | `auto p = std::make_unique<T>(...);` |
| `T* a = new T[n]; ... delete[] a;` | `std::vector<T> a(n);` |
| `T** grid = new T*[r]; ...` | `std::vector<std::vector<T>>` or flattened `std::vector<T>` |
| `void* opaque` | `std::variant`, templates, or `std::any` |

The raw forms still appear in interview questions, legacy code, and library internals — so you need to read them. You should rarely write them.
