// 2.4 — parameters receive copies; pass-by-value does not mutate the caller.
#include <iostream>

int add(int a, int b) {              // a, b are parameters
    return a + b;
}

void tryToZero(int x) {              // x is a copy of the caller's variable
    x = 0;                           // mutates the copy only
    std::cout << "  inside tryToZero, x = " << x << '\n';
}

int main() {
    std::cout << "add(2, 3)   = " << add(2, 3) << '\n';   // 2, 3 are arguments
    std::cout << "add(10, -4) = " << add(10, -4) << '\n';

    int n{ 42 };
    tryToZero(n);
    std::cout << "n after tryToZero(n) = " << n << '\n';  // still 42
}
