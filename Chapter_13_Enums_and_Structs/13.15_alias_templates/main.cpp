// 13.15 — Alias templates: parameterized type names.
#include <iostream>
#include <string>
#include <vector>

template <typename T, typename U>
struct Pair2 {
    T first;
    U second;
};

// Alias template that fixes the first parameter to int.
template <typename U>
using IntPair = Pair2<int, U>;

// Generic shorthand for a vector.
template <typename T>
using Vec = std::vector<T>;

int main() {
    IntPair<std::string> score{ 100, "Alice" };
    std::cout << score.first << ' ' << score.second << '\n';

    Vec<int> v{ 1, 2, 3, 4 };
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';

    // Vec<int> and std::vector<int> are the *same type* — transparent alias.
    std::vector<int>& ref{ v };
    std::cout << "vector size via ref: " << ref.size() << '\n';
}
