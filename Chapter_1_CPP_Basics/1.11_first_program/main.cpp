// 1.11 — first real program: double a number.
// To keep `make 1.11` non-interactive, the input is hard-coded.
// The interactive version is shown in comments.
#include <iostream>

int main()
{
    // Interactive form:
    //     std::cout << "Enter an integer: ";
    //     int x{};
    //     std::cin >> x;
    int x{ 7 };

    int doubled{ x * 2 };
    std::cout << "Double of " << x << " is " << doubled << ".\n";

    return 0;
}
