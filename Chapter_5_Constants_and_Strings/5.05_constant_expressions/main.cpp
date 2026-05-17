// 5.5 — what counts as a constant expression. The static_asserts compile
//       only because the inputs are compile-time known.
#include <iostream>

int getInput() {
    int x{};
    std::cin >> x;
    return x;
}

int main() {
    // (1) const int from a literal → constant expression.
    const int a{ 10 };
    static_assert(a == 10, "a must be a constant expression");

    // (2) const int from another constant expression → also constant.
    const int b{ a + 5 };
    static_assert(b == 15, "b is built from constant expressions");

    // (3) const int from a runtime function → NOT a constant expression.
    //     `c` is fixed for its lifetime, but the value isn't known at compile time.
    const int c{ getInput() };
    // static_assert(c >= 0, "..."); // error: c is not a constant expression

    // The classic test: array sizes need a constant expression.
    int fixed[a];          // OK — a is a constant expression
    // int dyn[c];         // error in standard C++ — c is not constant

    std::cout << "a=" << a << " b=" << b << " c=" << c
              << " sizeof(fixed)/sizeof(int)=" << (sizeof(fixed) / sizeof(int))
              << '\n';
}
