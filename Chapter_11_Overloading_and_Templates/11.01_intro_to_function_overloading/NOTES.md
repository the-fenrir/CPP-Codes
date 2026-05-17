# 11.1 — Introduction to function overloading

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-function-overloading/

## Why it matters
Without overloading you end up with `addInt`, `addDouble`, `addIntDouble` — names that exist only because C didn't let you reuse one. C++ lets the compiler pick the right function from the argument types. Same idea, less noise at the call site; the conceptual operation is "add", not "addInt vs. addDouble".

## Key points
- **Function overloading** = multiple functions sharing a name, distinguished by parameter list.
- Resolution happens **at compile time**, not at run time. `add(1, 2)` and `add(1.0, 2.0)` resolve to two different functions.
- Each overload must be tellable apart from the others by the compiler — covered in 11.2.
- Common, useful overloads: `print(int)` / `print(double)` / `print(const std::string&)`; `std::abs` for int / long / double.

## Code in this folder
- `main.cpp` — three `add()` overloads (int, double, string concat) called from one `main`.

## Gotchas
- Overload resolution is on **parameters**, not on return type alone (11.2).
- Don't overload when the operations aren't *semantically the same* — readers expect `print(x)` to print things, not also to delete files.

## Run
    make 11.01
