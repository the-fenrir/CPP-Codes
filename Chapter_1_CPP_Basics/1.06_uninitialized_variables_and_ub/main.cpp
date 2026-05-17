// 1.6 — uninitialized variables and undefined behavior.
// We deliberately do NOT trigger UB here; we only describe the trap.
#include <iostream>

int main()
{
    // The UB pattern — do not write code like this:
    //     int x;            // indeterminate value
    //     std::cout << x;   // ← reading it: undefined behavior

    // The safe pattern: always initialize.
    int x{};         // value-init to 0
    int y{ 42 };     // direct-list-init to 42

    std::cout << "x = " << x << '\n';
    std::cout << "y = " << y << '\n';

    return 0;
}
