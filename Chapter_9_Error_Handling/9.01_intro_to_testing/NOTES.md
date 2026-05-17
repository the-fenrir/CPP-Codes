# 9.1 — Introduction to testing your code

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-testing-your-code/

## Why it matters
"It compiles" tells you the syntax is legal. It says nothing about whether the program does what you intended. Testing is the discipline of confirming behavior matches intent — and doing it *cheaply enough* that you'll actually do it. The cost of a bug grows roughly with how far downstream it's caught: caught at the keyboard is free; caught in production is expensive.

## Key points
- **Software verification (testing)**: does the program behave as expected on the inputs we tried?
- **Unit test**: tests one small piece of code (typically one function) in isolation. Fast, focused, runs often.
- **Integration test**: tests how units cooperate. Slower, broader, runs less often.
- **Test early, test often**: writing one function and exercising it before moving on is cheaper than writing ten and debugging the interaction.
- **Preserve old tests**: don't delete a working test just because the feature looks finished — regression catches the *next* time someone changes the code.
- **Automate.** Manual testing scales like manual anything: you stop doing it. A `main()` that runs your test cases and reports pass/fail is a perfectly fine first test framework. You can graduate to Catch2 / GoogleTest later.

## Code in this folder
- `main.cpp` — a trivial function (`isPositive`) plus a hand-rolled test harness that runs a table of cases and prints PASS/FAIL. Demonstrates the cheapest possible "unit test framework" — no library, no dependencies.

## Gotchas
- **Testing only the happy path is barely testing.** Throw `0`, negatives, the empty string, max/min values at the function. Most bugs live at edges, not in the middle.
- **A test that never fails isn't a test, it's decoration.** If you can't articulate what change would make it fail, it's not testing anything.
- **Tests are code.** Bad tests rot, give false confidence, or fail intermittently. Treat them with the same care as production code.

## Run
    make 9.01
