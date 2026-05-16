# 15.7 — Static member functions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/static-member-functions/

## Why it matters
Static member functions are class-scoped functions with **no `this`**. They're how you give access to private static state, or expose a function that *conceptually* belongs to the class but doesn't act on a particular instance — like a factory function, or a utility that depends on the class's public types/statics.

## Key points
- Mark with `static` inside the class. **Not** repeated on the out-of-line definition.
- Has no `this` pointer ⇒ can't access non-static members. Can access static members of any access level (inside the class).
- Called via `ClassName::func()` or `obj.func()` (legal but discouraged — looks instance-y).
- A static member function **can't be `const`** (no `this` to qualify).
- Useful for: named constructors / factory methods, access to static state, namespace-like utility grouping.

## Code in this folder
- `main.cpp` — `Logger` with a private static counter and a static factory method.

## Gotchas
- Calling a static function via an instance compiles but obscures intent. Prefer `Class::func()`.
- Don't reach for "everything static" as a namespace replacement — actual `namespace` is the right tool when state isn't involved.

## Run
    make 15.07
