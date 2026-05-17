# 7.5 — Variable shadowing (name hiding)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/variable-shadowing-name-hiding/

## Why it matters
When an inner scope declares a name that already exists in an outer scope, the inner one **shadows** the outer for the duration of the inner scope. The outer name still exists — it's just not findable by unqualified lookup. This is the mechanism behind a whole category of "I thought I was modifying the outer variable" bugs.

## Key points
- A local can shadow another local in an outer block, a function parameter, or a global.
- Inside the shadowing scope, the unqualified name resolves to the inner variable. The outer is still reachable for **globals** via `::name`. There is *no* syntax to reach an outer **local** that's been shadowed — it's effectively invisible.
- Shadowing is legal and silent. Turn on `-Wshadow` to get warned about it.
- Best practice: don't shadow. Pick a different name; if you find yourself wanting to shadow, the outer name was probably too generic.

## Code in this folder
- `main.cpp` — a local shadowing a global (reach the global via `::`), a local shadowing another local (the outer one is unreachable).

## Gotchas
- `for (int i = 0; ...)` shadowing an outer `i` is the most common accidental case.
- Member functions shadowing inherited names is a related concept that bites in chapter 24; same rule.

## Run
    make 7.05
