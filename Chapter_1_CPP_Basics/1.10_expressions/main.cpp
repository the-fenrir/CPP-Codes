// 1.10 — expressions evaluate to a value.
#include <iostream>

int main()
{
    int a{ 2 };
    int b{ 3 };

    // Simple expressions.
    std::cout << "a + b           = " << (a + b)            << '\n';   // 5
    std::cout << "(a + b) * 4     = " << ((a + b) * 4)      << '\n';   // 20
    std::cout << "a < b           = " << (a < b)            << '\n';   // 1 (true)

    // Assignment is itself an expression — it has a value (the new value of x).
    int x{};
    int y{ (x = 10) + 1 };   // x is now 10; y is 11
    std::cout << "x=" << x << " y=" << y << '\n';

    return 0;
}
