# 27.10 — `std::move_if_noexcept`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdmove_if_noexcept/

## Why it matters
When `std::vector` resizes, it has to relocate every element to the new buffer. It wants to *move* them (faster), but moves come with a catch: if a move constructor throws midway, half the elements are in the new buffer, half in the old, and there's no clean way back — you've lost the **strong exception guarantee**. So the library compromises: if the element's move constructor is `noexcept`, move; otherwise, copy (which can fail safely — the old buffer is still intact). **That's the entire reason you mark move constructors `noexcept`.** The mechanism that picks one over the other is `std::move_if_noexcept`.

## Key points
- `std::move_if_noexcept(x)` returns an rvalue reference (enabling move) if T's move constructor is `noexcept`, otherwise a const lvalue reference (forcing copy).
- `std::vector<T>::push_back` (and friends) use this internally when reallocating, so that they preserve the strong guarantee.
- Practical consequence: **always mark your move constructor and move-assignment `noexcept`** when they actually don't throw — otherwise `std::vector` will copy your objects when growing.
- A throwing move is rare in practice (most moves are pointer swaps + nulls), so the `noexcept` mark is honest almost every time.
- If a type doesn't have a `noexcept` move but has a copy, `move_if_noexcept` returns a const-lvalue ref → vector copies. If a type has no copy (move-only) but a throwing move, it must move anyway — no choice.

## Code in this folder
- `main.cpp` — two near-identical types, one with `noexcept` move and one without. `std::move_if_noexcept` returns different categories for each; a tiny "vector grow" simulation prints "MOVE" or "COPY" so the choice is visible.

## Gotchas
- This is the single highest-leverage `noexcept` in your codebase. Forgetting it on a custom move ctor makes every `vector<T>` resize *copy* your elements. Major perf hit, silently.
- The check is on the **declaration**, not actual behavior. `noexcept` lies are punished by `std::terminate`, not by the optimizer.
- Move-only types with a throwing move are pathological — there's no copy fallback, so vectors of them lose the strong guarantee. Either make the move `noexcept` or don't store them in `vector`.

## Run
    make 27.10
