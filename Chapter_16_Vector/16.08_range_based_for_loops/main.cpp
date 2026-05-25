// 16.8 — range-based for: by value, by const ref, by ref.
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector v{ 1, 2, 3, 4, 5 };

    // By value: each x is a copy. Fine for int.
    std::cout << "by value:     ";
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';

    // By reference: mutate in place.
    for (auto& x : v) x *= 10;

    // By const reference: read-only, no copies — preferred default for big types.
    std::cout << "after *=10:   ";
    for (const auto& x : v) std::cout << x << ' ';
    std::cout << '\n';

    // Works for any range — vector of strings.
    std::vector<std::string> names{ "Alex", "Brad", "Charles" };
    std::cout << "names:        ";
    for (const auto& s : names) std::cout << s << ' ';
    std::cout << '\n';
}
