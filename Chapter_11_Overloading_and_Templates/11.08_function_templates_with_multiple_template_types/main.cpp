// 11.8 — independent T and U; auto return type.
#include <iostream>

template <typename T, typename U>
auto add(T x, U y) {
    return x + y;             // return type deduced from x + y
}

// T deduced only from x; second param is always int.
template <typename T>
T mult(T x, int y) {
    return x * y;
}

template <typename T, typename U>
auto sub(T x, U y) {
    return x - y;
}

int main() {
    std::cout << add(1, 2.5) << '\n';      // int + double → double, 3.5
    std::cout << add(2, 3)   << '\n';      // int + int    → int, 5

    std::cout << mult(2,   3) << '\n';     // T=int    → 6
    std::cout << mult(1.5, 3) << '\n';     // T=double → 4.5

    std::cout << sub(3,   2)   << '\n';    // int - int    → 1
    std::cout << sub(3.5, 2)   << '\n';    // double - int → 1.5
    std::cout << sub(4,   1.5) << '\n';    // int - double → 2.5
}
