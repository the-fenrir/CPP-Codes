# Chapter 27 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-27-summary-and-quiz/

## One-page recap

### Why exceptions (27.1)
- Return codes can't be used from constructors/operators and rot deep call chains with `if (err) return err;`.
- Exceptions decouple **detection** (deep) from **handling** (wherever the `catch` lives).
- Not for control flow — for "this function cannot deliver what it promised."

### Mechanics (27.2–27.3)
- Three keywords: `throw expr;`, `try { … }`, `catch (T) { … }`.
- Match is by **type**; first matching `catch` wins.
- An unmatched throw unwinds the stack — every function on the way out runs destructors for its locals. This is what makes RAII exception-safe by default.

### Boundaries (27.4)
- Escape from `main` → `std::terminate` → `std::abort`. Catch in `main` to get a clean diagnostic.
- `catch (...)` catches anything; must be last; useful only at the outermost boundary.
- Rethrow with bare `throw;` inside `catch (...)` to forward an unknown exception.

### Class exceptions & inheritance (27.5)
- Throw class objects, ideally derived from `std::exception` (or `std::runtime_error` / `std::logic_error` to inherit a message-carrying constructor).
- **Always catch by `const Base&`** — avoids slicing and lets `what()` dispatch virtually.
- Order `catch` from most-derived to least-derived; first match wins.

### Rethrow (27.6)
- `throw;` (bare) inside a `catch` rethrows the current exception with full dynamic type preserved.
- `throw e;` re-throws a *copy* of `e` — type sliced to the catch's declared type. Don't.

### Function try blocks (27.7)
- The only way to catch exceptions from a constructor's **member initializer list**.
- Inside the catch, the object never finished constructing → implicit rethrow at the end. You cannot suppress a constructor-init failure.

### Dangers (27.8)
- **Cleanup is RAII's job, not yours.** Raw `new` / locks / files leak on throw unless wrapped.
- **Destructors must not throw.** A throw during stack unwinding = `std::terminate`.
- **Don't throw across ABI boundaries** (shared libs, C interfaces).
- Three guarantee levels: basic, strong, nothrow. Aim for at least basic.

### `noexcept` (27.9)
- A **contract**, not a hint. Violating it terminates the program.
- Default: destructors and most special members are `noexcept`; user functions are not.
- `noexcept(expr)` is an operator that asks "is this expression non-throwing?" — used to propagate properties in templates.

### `move_if_noexcept` (27.10)
- `std::vector` reallocations need the strong guarantee. They move elements only when the move is `noexcept`, otherwise copy.
- Forgetting `noexcept` on a custom move ctor silently makes `std::vector<T>` slower on growth.
- The mechanism is `std::move_if_noexcept`, which returns `T&&` or `const T&` based on the move ctor's spec.

## Quiz

### Q1 — `Fraction` with throwing constructor

Write a `Fraction` class whose constructor takes a numerator and a denominator. If the denominator is `0`, the constructor must throw a `std::runtime_error` with a meaningful message. Provide a stream-output `operator<<` so `std::cout << f` prints `"n/d"`.

Then write a `main` that:

1. Prompts the user for a numerator and a denominator.
2. Constructs a `Fraction` from them inside a `try` block.
3. Prints the fraction on success.
4. Catches `const std::exception&` and prints `"Invalid denominator"` (plus the exception's `what()` for debugging).

The hint from the chapter is to catch by `const std::exception&`, not by a specific runtime_error subtype — keep the catch interface broad even when you know what you threw.

Example interaction:

```
Enter the numerator: 5
Enter the denominator: 0
Invalid denominator: Fraction: denominator cannot be zero
```

```
Enter the numerator: 3
Enter the denominator: 4
3/4
```

> Author's note: the constructor reports the failure *at the moment the invariant breaks*, not by leaving the object in a "zombie" state with a flag. That's the whole point of using an exception here — you can't construct an invalid `Fraction`.

### Q2 — Why catch by `const std::exception&` instead of `const std::runtime_error&`?

**Discussion question.** In Q1 we threw a `std::runtime_error`. Why does the solution catch `std::exception` (the base)?

**Answer.** Two reasons.

1. **Future-proofing the call site.** Today the constructor throws `std::runtime_error`. Tomorrow it might throw a more specific type (`InvalidDenominator : std::runtime_error`) or pick up an unrelated failure (an allocation throws `std::bad_alloc` — also derived from `std::exception`). A `catch (const std::exception&)` keeps handling all of those without the caller having to know the exact class hierarchy.
2. **Smallest surface for the caller.** The caller's job here is "tell the user the input was bad and move on" — it doesn't need the exact exception type to do that. Catch by the broadest type whose `what()` is useful, and let more-specific catches only exist where you'd actually behave differently.

The general rule is *catch by `const Base&`*; reach for a specific derived type only when the handler genuinely does something different for that type.

### Q3 — Why does the constructor throw instead of setting an error flag?

**Discussion question.** The constructor could also set `m_valid = false` and let callers check `f.valid()`. Why throw?

**Answer.** Three reasons:

1. **Invariants are easier to reason about when they can't be violated.** Every `Fraction` you can name has a non-zero denominator — there is no "half-constructed" state to handle in every member function (`print`, `multiply`, `reduce` would all need an early-return).
2. **Constructors have no return channel.** There's no return value to put an error code in. The two real options are "throw" and "construct successfully and lie about it" — the latter just postpones the bug to wherever the bad object is first used, far from the cause.
3. **The fail-fast property.** With the throwing constructor, `Fraction f{ n, 0 };` aborts the expression *right there*, at the call site that has the offending data. With the flag approach, the failure surfaces at the next `f.print()` call, possibly in unrelated code.

The cost is that callers must `try`/`catch`. That's intentional — the caller has the context to decide what to do (retry input, log, propagate further); the constructor only has the context to detect the problem.

## Run

    make 27.x

`quiz_solutions.cpp` has the worked code for Q1, with inline commentary explaining the design.
