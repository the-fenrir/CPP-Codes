# Chapter 27 — Exceptions

Chapter 27 covers C++ exception handling: when error codes break down, the `throw`/`try`/`catch` mechanism, how exceptions unwind the stack, catch-all handlers, throwing class objects and using inheritance hierarchies, rethrowing, function-try-blocks for constructor failures, the real downsides of exceptions, `noexcept`, and `std::move_if_noexcept`. By the end you can decide *whether* to use exceptions for a given failure, and write code that doesn't leak resources when one fires.

## Lessons

| # | Lesson |
|---|---|
| 27.01 | [The need for exceptions](27.01_need_for_exceptions/NOTES.md) |
| 27.02 | [Basic exception handling](27.02_basic_exception_handling/NOTES.md) |
| 27.03 | [Exceptions, functions & stack unwinding](27.03_functions_and_stack_unwinding/NOTES.md) |
| 27.04 | [Uncaught exceptions & catch-all handlers](27.04_uncaught_and_catch_all/NOTES.md) |
| 27.05 | [Exceptions, classes & inheritance](27.05_classes_and_inheritance/NOTES.md) |
| 27.06 | [Rethrowing exceptions](27.06_rethrowing_exceptions/NOTES.md) |
| 27.07 | [Function try blocks](27.07_function_try_blocks/NOTES.md) |
| 27.08 | [Exception dangers & downsides](27.08_dangers_and_downsides/NOTES.md) |
| 27.09 | [Exception specifications & `noexcept`](27.09_exception_specs_and_noexcept/NOTES.md) |
| 27.10 | [`std::move_if_noexcept`](27.10_move_if_noexcept/NOTES.md) |
| 27.x  | [Summary & quiz](27.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear. A few notes:

- **27.01 → 27.03** — motivation, mechanics, unwinding. Don't skip 27.03; "what `throw` actually does to the stack" is the whole reason RAII works.
- **27.05 → 27.06** — throw class objects (not ints), catch by `const&` to a base, and only rethrow with bare `throw;`. These three habits together cover ~90% of real usage.
- **27.07** is genuinely a corner-case (constructor member-init failures). Read it once so you recognize it; you won't write one often.
- **27.08** is the most important lesson in the chapter — exceptions are not free, and there are places (destructors, ABI boundaries, real-time loops) you must not throw from.
- **27.09 → 27.10** — `noexcept` is mostly a contract you mark move constructors with so that `std::vector` can use the move path in `move_if_noexcept`. Read them as a pair.
