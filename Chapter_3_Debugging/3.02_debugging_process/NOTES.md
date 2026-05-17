# 3.2 — The debugging process

> learncpp.com: https://www.learncpp.com/cpp-tutorial/the-debugging-process/

## Why it matters
"Debugging" feels like an art, but it's a five-step *process*. Naming the steps stops you from doing the worst thing — randomly changing code until the symptom goes away. That habit creates two new bugs for every one it accidentally fixes. Reading this lesson is the difference between "I poked at it until it worked" and "I know exactly why it was broken and why my fix works."

## Key points
The five steps, in order:
1. **Find the root cause.** Not the symptom. "It prints -1" is the symptom; "the loop reads one past the end" is the cause.
2. **Understand the problem.** Be able to explain in plain English *why* that cause produces *that* symptom. If you can't, you don't understand it yet.
3. **Determine a fix.** Often several candidates exist. Pick the one that addresses the root cause, not the one that hides the symptom.
4. **Repair the issue.** Make the change.
5. **Retest.** Confirm the bug is gone *and* nothing else broke. Re-run related tests, not just the one that reproduced the bug.

- Step 1 is where 90% of the time goes. The other four are mostly mechanical.
- Skipping step 2 is the classic mistake: you "fix" something, the symptom disappears, and you ship a program with the original bug intact plus a new mystery patch on top.

## Code in this folder
- `main.cpp` — a small "average of N numbers" program that silently produces the wrong answer. Walk it through the five steps yourself before reading the comment at the bottom.

## Gotchas
- "It works now" without an explanation is not a fix — it's a coincidence. If you don't know *why* it works, you don't know *when* it'll break again.
- Re-test step often gets cut short. Whatever change you made could have broken an unrelated case; run the full set, not just the one that reproduced.

## Run
    make 3.02
