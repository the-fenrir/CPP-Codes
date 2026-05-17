# 5.9 — `std::string_view` (part 2)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdstring_view-part-2/

## Why it matters
The basics in 5.8 make `string_view` look like a strict upgrade over `const std::string&`. The catch is *lifetime*: the view is just a pointer + length, and if the thing it points at goes away, you're reading freed memory with a smiling interface. This lesson is where the danger lives.

## Key points
- **Owners vs. viewers.** `std::string` owns; `std::string_view` views. A viewer is only valid while *something else* keeps the data alive.
- **Returning a view from a function** is almost always a bug if the view points at a local. The local dies at function return; the view dangles. Return `std::string` instead.
- **Storing a view as a class member** is fine *only* if you can guarantee the lifetime of the data it refers to — e.g., when it always points at string literals. Otherwise, store `std::string`.
- **A `std::string` can be reallocated.** If you take a `string_view` into a `std::string` and then push to that string, the view may dangle even though both are still in scope. Same problem as iterator invalidation.
- **View modifiers.** `remove_prefix(n)` / `remove_suffix(n)` shrink the view from the front/back. They don't allocate; they just adjust the pointer/length. Useful for parsing.
- **Converting back.** `std::string{ view }` copies; `view` itself does nothing for you. If you need to outlive the source, convert.

## Code in this folder
- `main.cpp` — `remove_prefix` / `remove_suffix` for parsing, a copy-out via `std::string{ view }`, and the dangling case (commented, with a note on UB).

## Gotchas
- Reading from a dangling `string_view` is undefined behavior. Sanitizers (`-fsanitize=address`) catch most cases. Don't rely on "it usually works."
- Implicit conversion from `std::string&&` (rvalue string) is dangerous: `std::string_view sv{ getString() };` views the returned temporary, which dies at the end of the full expression. Use `std::string` to receive instead.
- A view *into* a `std::string` invalidates the moment the string is resized — appending one char to `s` may move its buffer.

## Run
    make 5.09
