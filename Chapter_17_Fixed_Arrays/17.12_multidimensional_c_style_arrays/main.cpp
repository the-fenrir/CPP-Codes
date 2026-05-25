// 17.12 — multidimensional C-style arrays: declare, init, traverse.
#include <iostream>

int main() {
    // Fully specified — 2 rows, 3 columns. Inner braces document the rows.
    int grid[2][3] {
        { 1, 2, 3 },
        { 4, 5, 6 }
    };

    // Outer dimension deduced. Inner dimension is part of the element type
    // and must be spelled out.
    int grid2[][3] {
        { 7,  8,  9  },
        { 10, 11, 12 },
        { 13, 14, 15 }
    };

    // Print row-by-row with nested range-for.
    std::cout << "grid (2x3):\n";
    for (const auto& row : grid) {
        for (int x : row) std::cout << x << '\t';
        std::cout << '\n';
    }

    std::cout << "grid2 (3x3, outer dim deduced):\n";
    int total { 0 };
    for (const auto& row : grid2) {
        for (int x : row) {
            std::cout << x << '\t';
            total += x;
        }
        std::cout << '\n';
    }
    std::cout << "sum = " << total << '\n';

    // Index-based access uses the underlying *(*(g + r) + c) semantics.
    std::cout << "grid[1][2] = " << grid[1][2] << '\n';
}
