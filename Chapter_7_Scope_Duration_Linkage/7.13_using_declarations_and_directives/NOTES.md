# 7.13 — Using declarations and using directives

> learncpp.com: https://www.learncpp.com/cpp-tutorial/using-declarations-and-using-directives/

## Why it matters
`using namespace std;` is the first piece of C++ folklore most people learn — and it's usually wrong. This lesson distinguishes a `using` **declaration** (precise, one name) from a `using` **directive** (broad, every name), and gives you a rule for where each is safe.

## Key points
- **Using declaration**: `using std::cout;` — pulls *one* name into the current scope. Targeted, low-risk.
- **Using directive**: `using namespace std;` — pulls *every* name in the namespace into the current scope. Useful interactively, dangerous in any larger context.
- Both honor scope: place them inside a function and the import dies at `}`. That's usually the right place.
- **Never** put a `using` directive at namespace scope in a header — every file that includes it inherits the pollution. ODR violations and ambiguity errors follow.
- Risk: a `using namespace X;` at file scope can quietly change which function a call resolves to when a new name is added to `X` later. That's a silent behavior change at upgrade time.

## Code in this folder
- `main.cpp` — `using std::cout;` (declaration) inside a function, then a contrived ambiguity that a `using namespace` at file scope would have caused.

## Gotchas
- A `using` declaration *can* still cause shadowing/ambiguity, just on a smaller scale.
- `using` inside a class body has yet another meaning (member-`using` for inheritance, chapter 24). Same keyword, different purpose.
- `using` aliases for *types* (`using Vec = std::vector<int>;`) is yet another use — covered in chapter 10.

## Run
    make 7.13
