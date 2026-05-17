// 10.7 — type aliases: a second name for an existing type.
#include <iostream>
#include <string>
#include <vector>

// Old C-style.
typedef double DistanceTypedef;

// Modern C++.
using Distance = double;
using Degrees  = double;
using Radians  = double;

// Aliases shine on long library types.
using StringIntList = std::vector<std::pair<std::string, int>>;

void printAll(const StringIntList& xs) {
    for (const auto& p : xs)
        std::cout << "  " << p.first << " = " << p.second << '\n';
}

int main() {
    DistanceTypedef d1 = 5.0;
    Distance        d2 = 10.0;
    std::cout << "d1=" << d1 << "  d2=" << d2 << '\n';

    // Aliases are NOT new types: Degrees and Radians are both just double.
    Degrees deg = 90.0;
    Radians rad = deg;   // silently allowed — the compiler sees double = double
    std::cout << "rad after rad = deg: " << rad << "  (no safety, just a name)\n";

    StringIntList scores{ {"alice", 1}, {"bob", 2} };
    printAll(scores);
}
