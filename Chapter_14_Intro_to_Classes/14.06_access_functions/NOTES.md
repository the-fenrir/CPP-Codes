# 14.6 — Access functions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/access-functions/

## Why it matters
Once data is private (14.5), you need a sanctioned way to read/write it from outside. **Access functions** (getters and setters) are it. But not every private variable deserves them — a class that mirrors every private member with a public `get_X / set_X` pair has private members in name only. Access functions exist to *let you control* what's exposed, not to dump it back out.

## Key points
- **Getter** = reads state; should be `const`. **Setter** = writes state; not `const`.
- Naming styles vary: `getX()/setX()` or `x()/setX()` are both common. Pick one and stay consistent.
- A getter can return by value (safe, copies), by `const&` (cheap, no copy, caller must respect lifetime), or by `&` (gives a write handle — careful!).
- **Don't reflexively add getters/setters for everything.** Ask: does the *caller* have a legitimate reason to know or change this? If not, leave it sealed.
- Computed access functions (e.g. `area()` from `width` + `height`) are usually a better interface than raw getters.

## Code in this folder
- `main.cpp` — a `Temperature` class with a validated setter and a computed access function.

## Gotchas
- A setter without validation is just a more verbose `public:` field.
- Returning `const std::string&` from a getter is fine — but if the caller copies it to a `std::string&`, you've still made a copy. Returning `std::string_view` (C++17) is often the better default for read-only strings.

## Run
    make 14.06
