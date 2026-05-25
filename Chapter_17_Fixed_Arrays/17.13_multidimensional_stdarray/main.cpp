// 17.13 — std::array<std::array<T, Cols>, Rows>: declare, init, traverse.
#include <array>
#include <iostream>

constexpr std::size_t Rows { 3 };
constexpr std::size_t Cols { 4 };
using Grid = std::array<std::array<int, Cols>, Rows>;

void print(const Grid& g) {
    for (const auto& row : g) {
        for (int x : row) std::cout << x << '\t';
        std::cout << '\n';
    }
}

int main() {
    // Strict form needs double outer braces (outer std::array wrapping an
    // internal C-style array). Brace elision often lets you write one set;
    // we keep both for clarity.
    Grid g {{
        { 1,  2,  3,  4  },
        { 5,  6,  7,  8  },
        { 9, 10, 11, 12 }
    }};

    print(g);

    // Each row is a value, not a pointer — copy, compare, return.
    std::array<int, Cols> firstRow { g[0] };       // copy
    bool sameRow { firstRow == g[0] };             // element-wise ==
    std::cout << "row copy equals original? " << std::boolalpha << sameRow << '\n';

    // Sum every element with nested range-for.
    int total { 0 };
    for (const auto& row : g)
        for (int x : row)
            total += x;
    std::cout << "sum = " << total << '\n';
}
