# 2.9 — Naming collisions and an introduction to namespaces

> learncpp.com: https://www.learncpp.com/cpp-tutorial/naming-collisions-and-an-introduction-to-namespaces/

## Why it matters
Once you have multiple files (and any non-trivial program does), two libraries can both define `print()` or `Vector`. Without a way to scope names, you'd be stuck renaming everyone else's code. Namespaces let each library hand out names without stepping on each other.

## Key points
- A **namespace** is a named scope for declarations. Same name in different namespaces = different entities.
- The standard library lives in `std::`. `std::cout`, `std::string`, `std::vector`.
- `::` is the **scope resolution operator**.
- `using namespace std;` dumps all of `std` into the current scope — convenient, but the original source of namespace collisions. **Avoid it at file scope**, especially in headers.
- A using *declaration* (`using std::cout;`) brings in just one name and is much safer.
- Unqualified calls to standard names work in some contexts via **argument-dependent lookup (ADL)** — that's an advanced topic; for now, qualify with `std::`.

## Code in this folder
- `main.cpp` — defines `math::add` and `string_ops::add`, two functions with the same name in different namespaces, called unambiguously.

## Gotchas
- `using namespace std;` in a header file pollutes every TU that includes it — never do this.
- Two namespaces can both have a `swap`; without qualification, ADL may pick the "wrong" one.
- Don't define your own things in `namespace std` (it's undefined behavior, with narrow exceptions like specializing templates).

## Run
    make 2.09
