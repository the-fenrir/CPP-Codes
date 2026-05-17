# 12.12 — Return by reference and return by address

> learncpp.com: https://www.learncpp.com/cpp-tutorial/return-by-reference-and-return-by-address/

## Why it matters
Returning by reference (`T&`) or by address (`T*`) avoids a copy and lets the caller modify the returned object. It's also the most dangerous pattern in the chapter: returning a reference to a local is the textbook example of dangling — undefined behavior that often *appears* to work, hiding the bug.

## Key points
- **Return by reference is fine** when returning something whose lifetime outlives the call: a function parameter passed by reference, a member of a long-lived object, a `static` local, a global.
- **Return by value** is the default. With C++17 mandatory copy elision and NRVO, returning a local by value is essentially free.
- Return by address is rarer; same lifetime rules as by-reference, plus nullability.
- Member functions returning `T&` to a data member let callers mutate the object through the call site (`obj.field() = 5`). Often you want `const T&` instead — covered in chapter 14.
- A function returning `T&` produces an **lvalue** call expression (`f() = x;` is legal). A function returning `T` produces an **rvalue**.

## Code in this folder
- `main.cpp` — return by value, by reference to a static, by reference to a passed-in argument. Dangling case shown in **comments only**.

## Gotchas
- **Returning a reference/pointer to a local is UB.** Compilers warn for the obvious case but not always for indirect ones. The local dies at the closing `}` — the reference points at freed stack space.
- **Returning a reference to a function parameter passed by value** is also UB — the parameter is local to the function.
- Returning a reference to a temporary created in the return statement is UB — temporaries die at the end of the full expression.
- Returning a reference to a `std::string&` returned by another function is fine *if* the underlying object outlives the call chain. Trace lifetimes carefully.

## Run
    make 12.12
