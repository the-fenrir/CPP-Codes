// 17.4 — std::array of class types, with and without elided inner braces.
#include <array>
#include <iostream>

struct House {
    int number{};
    int stories{};
    int rooms{};
};

void print(const House& h) {
    std::cout << "House #" << h.number
              << " (" << h.stories << " stories, " << h.rooms << " rooms)\n";
}

int main() {
    // Strict form: outer braces for std::array, inner braces for the wrapped
    // C-style array, innermost braces for each House aggregate.
    std::array<House, 3> strict {{
        { 1, 2, 5 },
        { 2, 1, 3 },
        { 3, 3, 9 }
    }};

    // Explicit-element form: write House{...} for each. Brace elision then
    // applies automatically — only one outer pair of braces needed.
    std::array<House, 3> explicitElems {
        House{ 1, 2, 5 },
        House{ 2, 1, 3 },
        House{ 3, 3, 9 }
    };

    for (const auto& h : strict)        print(h);
    std::cout << "---\n";
    for (const auto& h : explicitElems) print(h);
}
