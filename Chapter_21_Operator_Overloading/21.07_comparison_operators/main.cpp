// 21.7 — C++20 spaceship + defaulted ==: one declaration, all six comparisons.
#include <algorithm>
#include <compare>
#include <iostream>
#include <string>
#include <vector>

struct Car {
    std::string make;
    std::string model;

    // Lexicographic over members in declaration order.
    auto operator<=>(const Car&) const = default;
    bool operator==(const Car&) const = default;
};

std::ostream& operator<<(std::ostream& out, const Car& c) {
    return out << c.make << ' ' << c.model;
}

int main() {
    Car a{ "Honda", "Civic" };
    Car b{ "Honda", "Civic" };
    Car c{ "Toyota", "Corolla" };

    std::cout << std::boolalpha;
    std::cout << "a == b: " << (a == b) << '\n';
    std::cout << "a != c: " << (a != c) << '\n';
    std::cout << "a <  c: " << (a <  c) << '\n';
    std::cout << "c >= a: " << (c >= a) << '\n';

    std::vector<Car> v{ c, a, b };
    std::sort(v.begin(), v.end());
    for (const auto& car : v) std::cout << car << '\n';
}
