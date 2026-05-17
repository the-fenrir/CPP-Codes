// 5.1 — named constants: compile-time-fixed vs. runtime-initialized,
//       and const function parameters.
#include <iostream>

// `const` parameter: a promise inside the function not to reassign `n`.
// The caller doesn't care; this is purely a self-discipline tool.
void printDoubled(const int n) {
    // n = n * 2; // error: assignment of read-only parameter
    std::cout << "doubled: " << n * 2 << '\n';
}

int main() {
    const int maxStudents{ 30 };          // value fixed at compile time
    std::cout << "max students: " << maxStudents << '\n';

    // maxStudents = 31; // error: assignment of read-only variable

    // A `const` whose value is decided at runtime is still a const —
    // it just isn't a *constant expression*. See 5.5–5.6.
    std::cout << "enter your age: ";
    int input{};
    std::cin >> input;
    const int age{ input };
    std::cout << "age locked in as " << age << '\n';

    printDoubled(age);
}
