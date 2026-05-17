// 11.6 — one bigger() that works for any type supporting <.
// (Named bigger() instead of max() so ADL doesn't drag in std::max via <string>.)
#include <iostream>
#include <string>

template <typename T>
T bigger(T a, T b) {
    return (a < b) ? b : a;
}

// C++20 abbreviated form — each `auto` is an independent template parameter.
auto add(auto a, auto b) {
    return a + b;
}

int main() {
    std::cout << bigger(3, 7) << '\n';                 // T = int
    std::cout << bigger(2.5, 1.5) << '\n';             // T = double
    std::cout << bigger(std::string{"apple"},          // T = std::string
                        std::string{"banana"}) << '\n';

    // Force T explicitly when deduction can't pick:
    std::cout << bigger<double>(3, 7.5) << '\n';

    std::cout << add(1, 2.5) << '\n';                  // abbreviated: T=int, U=double → 3.5
}
