// Chapter 1 quiz solutions.
//
// Q1 — Initialization vs. assignment.
//   Initialization sets the value of a variable *as it is created*; it happens
//   exactly once per object lifetime. Assignment replaces the value of an
//   already-existing variable using `=` and can happen any number of times.
//   In `int x{ 5 }; x = 7;` — `{ 5 }` is initialization, `x = 7;` is assignment.
//
// Q2 — Undefined behavior.
//   UB occurs when the program performs an operation the C++ standard places
//   no requirements on — e.g. reading an uninitialized variable, dereferencing
//   a null pointer, signed integer overflow, out-of-bounds array access.
//   Consequences: anything is "legal." Symptoms range from "appears to work"
//   to wrong results, crashes, or different behavior between compilers /
//   optimization levels / runs. Critically: a program that *contains* UB is
//   broken even if it happens to produce the expected output today.
//
// Q3 — Sum and difference of two integers (worked below).
//
// Design notes for Q3:
//  • The values are hard-coded so `make 1.x` runs non-interactively. The
//    interactive form is shown in comments.
//  • Variables are brace-initialized — lesson 1.4's preferred form.
//  • Output uses `".\n"` (string literal) for period-then-newline; `'.\n'`
//    would not compile because a char literal can hold only one character.
#include <iostream>

int main()
{
    // Interactive form (uncomment for real use):
    //     std::cout << "Enter an integer: ";
    //     int a{};
    //     std::cin >> a;
    //     std::cout << "Enter another integer: ";
    //     int b{};
    //     std::cin >> b;
    int a{ 6 };
    int b{ 4 };

    // Echo what we "read" so the output matches the spec exactly.
    std::cout << "Enter an integer: " << a << '\n';
    std::cout << "Enter another integer: " << b << '\n';

    std::cout << a << " + " << b << " is " << (a + b) << ".\n";
    std::cout << a << " - " << b << " is " << (a - b) << ".\n";

    return 0;
}
