// 1.3 — defining variables (objects with names).
#include <iostream>

int main()
{
    int x;          // definition: reserves memory for an int named x. Value is indeterminate!
    x = 5;          // assignment: now x holds 5.

    int y{ 42 };    // definition + initialization in one step (preferred — see 1.4).

    std::cout << "x = " << x << '\n';
    std::cout << "y = " << y << '\n';

    return 0;
}
