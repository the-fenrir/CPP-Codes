# 3.3 — A strategy for debugging

> learncpp.com: https://www.learncpp.com/cpp-tutorial/a-strategy-for-debugging/

## Why it matters
Step 1 of 3.2 ("find the root cause") is the hard one. This lesson gives you the actual procedure for *doing* it — a binary-search-style hunt that turns a vague "something's wrong" into a specific line of code. It's the single highest-leverage habit in this chapter.

## Key points
- **Reproduce the bug reliably first.** A bug you can't reproduce on demand cannot be debugged — you'll never know if your "fix" worked. Reduce the inputs until you have the smallest case that still fails.
- **Hypothesize → test → narrow.** Pick a point in the program; check whether the state is correct *at* that point. If yes, the bug is *after*; if no, the bug is *before*. Repeat. This is binary search over the program's execution.
- Useful "checkpoints" to look at:
  - Function entry / exit (are the args what you expect? is the return value right?)
  - Before/after a loop (was the precondition met? is the result right?)
  - Branch boundaries (which side did we actually take?)
- **One change at a time.** If you change three things and the bug goes away, you don't know which fixed it — or whether two of your changes introduced new bugs that just happen to cancel.
- **Keep notes.** Even informally. "Checked X at line 40, was 7, expected 7. Checked Y at line 55, was 0, expected 3." After ten checks you will not remember which were which.

## Code in this folder
- `main.cpp` — a `findMax` over a vector that returns the wrong value on some inputs. Practice the binary-search hunt: add a print at function entry, then mid-loop, then at return, and narrow the bug down yourself.

## Gotchas
- Changing code to "see if that fixes it" without a hypothesis is gambling, not debugging.
- If a bug only happens "sometimes," suspect (in order): uninitialized memory, depending on iteration order of an unordered container, threading, or non-determinism in inputs (time, random, network). All four reduce to "make it deterministic before debugging."

## Run
    make 3.03
