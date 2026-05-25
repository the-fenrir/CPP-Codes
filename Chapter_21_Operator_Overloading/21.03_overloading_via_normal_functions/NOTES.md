# 21.3 — Overloading operators using normal (non-friend, non-member) functions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/overloading-operators-using-normal-functions/

## Why it matters
If your class already exposes everything an operator needs through its **public** interface, the overload doesn't need `friend` — it can just be a plain free function. This is the form to default to. It keeps the class's friend list short and makes the operator easy to read.

## Key points
- Same syntax as a friend overload, minus the `friend` keyword and the class-body declaration.
- Place the function in the same namespace as the class so ADL (argument-dependent lookup) finds it.
- The Scott Meyers guideline (mentioned in 14.x): *prefer non-member, non-friend functions when both can do the job*. It restricts what the operator can break — it can only depend on what every other caller already depends on.

## Code in this folder
- `main.cpp` — `Cents` exposing `value()`, with `operator+` implemented entirely against the public interface.

## Gotchas
- If you later make members private and remove the accessor, the overload silently breaks. That's a feature: it forces the *operator* to depend on the same interface external callers use.
- If the operator needs to mutate the object's private state (e.g. `operator+=`), it usually has to be a **member**; that's the next lesson.

## Run
    make 21.03
