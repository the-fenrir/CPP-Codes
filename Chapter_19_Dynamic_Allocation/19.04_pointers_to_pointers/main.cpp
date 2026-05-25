// 19.4 — pointers to pointers; jagged vs flattened 2D dynamic arrays.
//
// Two ways to build the same 3x4 grid:
//   (1) jagged: int** with per-row allocation. Two-level free in reverse.
//   (2) flat:   int* of size rows*cols, indexed with row*cols + col.
//
// (1) is the textbook double-pointer pattern. (2) is what you should
// actually write — one allocation, one free, contiguous in memory.
#include <iostream>

int main() {
    constexpr std::size_t rows{ 3 };
    constexpr std::size_t cols{ 4 };

    // ── (1) jagged: array of row pointers ──────────────────────────────
    int** grid{ new int*[rows] };          // outer: row-pointer array
    for (std::size_t r = 0; r < rows; ++r)
        grid[r] = new int[cols]{};         // inner: each row, zero-init

    for (std::size_t r = 0; r < rows; ++r)
        for (std::size_t c = 0; c < cols; ++c)
            grid[r][c] = static_cast<int>(r * cols + c);

    std::cout << "jagged 2D (int**):\n";
    for (std::size_t r = 0; r < rows; ++r) {
        for (std::size_t c = 0; c < cols; ++c)
            std::cout << grid[r][c] << '\t';
        std::cout << '\n';
    }

    // free in reverse order: each row first, then the outer array
    for (std::size_t r = 0; r < rows; ++r) delete[] grid[r];
    delete[] grid;
    grid = nullptr;

    // ── (2) flattened: one block, manual indexing ──────────────────────
    int* flat{ new int[rows * cols]{} };
    auto at = [&](std::size_t r, std::size_t c) -> int& {
        return flat[r * cols + c];
    };

    for (std::size_t r = 0; r < rows; ++r)
        for (std::size_t c = 0; c < cols; ++c)
            at(r, c) = static_cast<int>(r * cols + c);

    std::cout << "\nflattened 2D (int* with row*cols+col):\n";
    for (std::size_t r = 0; r < rows; ++r) {
        for (std::size_t c = 0; c < cols; ++c)
            std::cout << at(r, c) << '\t';
        std::cout << '\n';
    }

    delete[] flat;                          // one new[], one delete[]
    flat = nullptr;

    // ── (3) modern equivalent ──────────────────────────────────────────
    // std::vector<int> v(rows * cols);
    // v[r*cols + c] = ...;
    // // no delete needed; v cleans up automatically.
}
