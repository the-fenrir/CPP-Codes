# 20.2 — The stack and the heap

> learncpp.com: https://www.learncpp.com/cpp-tutorial/the-stack-and-the-heap/

## Why it matters
Every variable lives somewhere. Knowing *where* explains the rules you've been following on faith: why locals vanish at `}`, why returning `&local` is a bug, why `new` has to be paired with `delete`, why huge local arrays crash the program before they're even used. Stack vs. heap is the mental model that turns those rules into one principle.

## Key points
- **Stack** — LIFO region of memory. Each function call pushes a *stack frame* holding parameters, locals, and bookkeeping; the frame pops on return. Fast (pointer bump), automatically managed, but small (typically ~1 MB on Windows, ~8 MB on Linux).
- **Heap** — large pool of memory you allocate from explicitly with `new` (and free with `delete`). Slower allocation, manually managed, but bounded only by available RAM.
- Local objects are on the stack. Objects created with `new` are on the heap; the pointer to them often lives on the stack.
- Returning a pointer/reference to a local is undefined behavior — the frame is gone. Returning a pointer to a `new`'d object is fine, but now the caller owns it.
- Huge stack allocations (`int arr[100'000'000]`) blow the stack at function entry — segfault or stack overflow before any code runs. Big buffers go on the heap (or, in real code, in `std::vector`).
- Recursion uses one frame per level. Deep recursion ⇒ stack overflow. (See 20.3.)
- Modern C++: prefer `std::vector`, `std::string`, `std::unique_ptr`, `std::make_unique` over raw `new`/`delete`. They put the big payload on the heap but manage the lifetime for you.

## Code in this folder
- `main.cpp` — same data allocated on the stack and on the heap; a function that returns a heap object; demonstration that locals die on return.

## Gotchas
- "Stack" and "heap" are *implementation* terms — the standard says "automatic storage duration" and "dynamic storage duration." Same thing, fancier names.
- `new int[n]` returns a pointer, but you must free it with `delete[] p` — `delete p` is UB for array-new.
- Stack frames aren't zeroed on entry; uninitialized locals hold garbage.

## Run
    make 20.02
