# 22.4 — `std::move`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdmove/

## Why it matters
Sometimes you have an lvalue that you *know* you won't use again, and you want the move overload to run instead of the copy. `std::move` is the cast that tells the compiler exactly that: "treat this lvalue as if it were an rvalue." It's just a cast — no actual moving happens until the move ctor/assignment runs.

## Key points
- `std::move(x)` produces an rvalue reference to `x`. It does not move anything by itself.
- After `std::move(x)`, `x` is **valid but unspecified**. Reading it (other than to assign or destroy) is technically defined but meaningless.
- Useful when:
  - swapping (`a = std::move(b); b = std::move(tmp);`),
  - pushing a local into a container (`v.push_back(std::move(local))`),
  - implementing your own move ctor/assign that forwards member subobjects.
- `std::move_if_noexcept` exists for the case where you want move when it's safe (noexcept) and copy otherwise.
- Don't `return std::move(local)` from a function returning by value — it inhibits NRVO. Just `return local;`.

## Code in this folder
- `main.cpp` — moves a `std::string` (cheap-to-move type) into a vector, and shows the "valid but unspecified" rule with a print after `std::move`.

## Gotchas
- `std::move` on a `const T` does nothing useful — you'd get `const T&&` which binds to a `const T&` copy overload. So `const` members can't be moved.
- Calling `std::move` and *then* reading the value back is a code smell. The intent of `std::move` is "I am done with this."
- `std::move` is a function template defined in `<utility>` — easy to forget the include.

## Run
    make 22.04
