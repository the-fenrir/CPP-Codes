# 23.5 — Dependencies

> learncpp.com: https://www.learncpp.com/cpp-tutorial/dependencies/

## Why it matters
The weakest relationship. A `Point` *uses* `std::ostream` to print itself — but it doesn't store one, doesn't have a member, doesn't own one, never thinks about one outside the call. The dependency is born when the function is called and dies when it returns. Most function calls in a program are dependencies; that's why nobody usually labels them. The reason to name it is to contrast it with association: when the link is short-lived enough that you don't need a member, **don't add one**.

## Key points
- Dependency = "uses-a, *for one operation*." One object calls another's functionality, then forgets it.
- No member stored. The "needed" object arrives as a **parameter**, or is **constructed locally**, or is a **global** like `std::cout`.
- Always **unidirectional** — there's nothing to be bidirectional about; the link doesn't live long enough.
- Practical heuristic: if `A` mentions `B` only inside a single function body and you never write `A::m_b`, the relationship is dependency. If you find yourself wanting a member, you've drifted into association.
- Dependencies make code easier to test (pass in a fake `std::ostream`, fake clock, fake socket) and easier to compose. They're the loosest possible coupling.

## Code in this folder
- `main.cpp` — `Point::print(std::ostream&)` depends on `std::ostream` for the duration of the call only. Different sinks can be passed in; `Point` is unaware.

## Gotchas
- A dependency that grows long-lived (you start passing the same object every call) is begging to become an association. That's fine — promote it deliberately, don't just bolt on a member because it's convenient.
- "Depending on" `std::vector` to implement your class is also technically a dependency, but the chapter is about *runtime object usage*, not header-level coupling. Don't confuse the two senses.

## Run
    make 23.05
