# 11.3 — Function overload resolution and ambiguous matches

> learncpp.com: https://www.learncpp.com/cpp-tutorial/function-overload-resolution-and-ambiguous-matches/

## Why it matters
The compiler runs a fixed algorithm to pick which overload a call refers to. When more than one overload is "equally good," it gives up with an *ambiguous match* error. Most of the surprises in overloading (and templates, later) are really surprises about this algorithm.

## Key points
Roughly, the compiler tries these conversion tiers in order; the first tier that has *exactly one* matching overload wins:

1. **Exact match.** Includes trivial conversions (`int` → `const int`, `T&` → `T`, array → pointer).
2. **Promotion.** `char`/`short` → `int`, `float` → `double`. Cheap and safe.
3. **Standard conversion.** Numeric conversions (`int` → `double`), pointer conversions, etc. Lossy in principle.
4. **User-defined conversion.** Constructor or `operator T()`.
5. **Ellipsis** (`...`). Last resort.

Within a single tier, multiple matches ⇒ **ambiguous match** error.

- Promotions are preferred over conversions: with `print(int)` and `print(double)`, a `short` argument picks `print(int)` (promotion), not `print(double)` (conversion).
- Two equally good conversions ⇒ ambiguous. Example: `print(long)` + `print(double)` called with `print(5)` — `int` converts to either, neither is better.

## Code in this folder
- `main.cpp` — three calls that work (one per tier 1–3), and two ambiguity demonstrations commented out with their explanations.

## Gotchas
- "Best match" is decided per-argument first, then combined: an overload wins only if it's at least as good as the alternatives for *every* argument and strictly better for *at least one*.
- Mixing default arguments with overloads is a common ambiguity source — see 11.5.
- Templates participate in resolution alongside non-templates; non-template wins ties (11.7 / quiz Q4).

## Run
    make 11.03
