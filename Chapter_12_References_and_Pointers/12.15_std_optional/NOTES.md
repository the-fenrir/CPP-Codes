# 12.15 — `std::optional`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdoptional/

## Why it matters
"This function might not return a value" is a common need. Historically it was modeled with sentinel values (`-1`, `""`), out-parameters + bool returns, or raw pointers. Each leaks ownership concerns, ambiguity, or null checks. `std::optional<T>` (C++17, `<optional>`) is the right modern answer: either a `T` or nothing, no extra allocation, no nullability for the *type*, no sentinel.

## Key points
- `std::optional<T>` holds either an instance of `T` or no value (`std::nullopt`).
- Construct: `std::optional<int> o;` (empty), `std::optional<int> o{ 5 };` (engaged), `o = std::nullopt;` (reset).
- Check: `if (o)` or `o.has_value()`.
- Access: `*o` or `o.value()` (latter throws `std::bad_optional_access` if empty). `o.value_or(default)` returns the default when empty.
- The value lives **inside** the optional — no heap allocation. `sizeof(optional<T>) == sizeof(T) + alignment`.
- Use cases: "maybe parses," "lookup may miss," "function may not have a result." Replaces most legitimate uses of `T*` for optional values.
- Don't use it as a smart pointer (it copies the value). Don't use it for cheap-defaultable types where the default already means "absent."

## Code in this folder
- `main.cpp` — engaged/empty optionals, `value_or`, `tryParseInt` rewritten.

## Gotchas
- `o.value()` throws on empty — fine if that's an invariant violation, but `*o` (no check) is UB if empty. Use `if (o)` first or `value_or`.
- Don't store references in optionals — `std::optional<T&>` is not allowed in C++20. Use `std::optional<std::reference_wrapper<T>>` or a pointer.
- `optional<bool>` has three states (empty, false, true) — sometimes useful, sometimes a smell.
- Compared to exceptions: optional is for *expected* absence (a key not in a map); exceptions are for *exceptional* failure (out of memory, file I/O error).

## Run
    make 12.15
