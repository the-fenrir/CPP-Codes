// 17.7 — declaring and initializing C-style arrays.
#include <iostream>
#include <iterator>   // std::size

int main() {
    // Value-initialize to all zeros. Skip the braces and the values are
    // INDETERMINATE — reading them is UB.
    int zeros[5] {};

    // Partial init: first three set, last two zeroed (rule for missing values).
    int partial[5] { 1, 2, 3 };

    // Size deduced from initializer length.
    int deduced[] { 10, 20, 30, 40 };

    std::cout << "zeros   :";
    for (std::size_t i { 0 }; i < std::size(zeros); ++i)
        std::cout << ' ' << zeros[i];
    std::cout << '\n';

    std::cout << "partial :";
    for (int x : partial) std::cout << ' ' << x;
    std::cout << '\n';

    std::cout << "deduced (" << std::size(deduced) << " elements):";
    for (int x : deduced) std::cout << ' ' << x;
    std::cout << '\n';

    // No ==, no assignment, no return by value — that's why std::array exists.
}
