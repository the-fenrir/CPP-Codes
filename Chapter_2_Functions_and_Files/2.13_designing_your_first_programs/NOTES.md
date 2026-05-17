# 2.13 — How to design your first programs

> learncpp.com: https://www.learncpp.com/cpp-tutorial/how-to-design-your-first-programs/

## Why it matters
Most beginner pain isn't syntax — it's sitting in front of an empty `main()` with no idea what to type. This lesson gives you a repeatable process: define the goal, sketch the steps, decompose into functions, then write code. The earlier you internalize "design first, type second," the less code you throw away.

## Key points
- **Define the goal**: write down, in one sentence, what the program should do for its user.
- **Define requirements**: inputs, outputs, constraints. What does it consume, what does it produce?
- **Define the tools**: language features and libraries you'll need.
- **Decompose into functions**: each step from your sketch becomes a function. Start with stubs that just print "called fooStep".
- **Implement incrementally**: get something running end-to-end first, then improve each piece.
- **Test as you go**: don't write 200 lines and *then* try to compile.
- **Iterate**: first version is for you; second version is for someone else.

## Code in this folder
- `main.cpp` — a tiny program designed using the recipe above: prompt → read → compute → print. Each step is a named function.

## Gotchas
- "I'll just start typing" works for 20-line programs and falls apart fast above that.
- Premature optimization: don't introduce abstraction (classes, templates) until the second pass, when you actually know what varies.
- A function whose name needs the word "and" probably wants to be split.

## Run
    make 2.13
