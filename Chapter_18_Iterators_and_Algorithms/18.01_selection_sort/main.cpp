// 18.1 — selection sort by hand vs. std::sort on the same array.
#include <algorithm>
#include <array>
#include <iostream>
#include <utility>

void print(std::string_view label, const std::array<int, 6>& a) {
    std::cout << label;
    for (int x : a) std::cout << ' ' << x;
    std::cout << '\n';
}

int main() {
    // ── Hand-rolled selection sort ──────────────────────────────
    std::array<int, 6> a{ 30, 50, 20, 10, 40, 60 };
    print("before:       ", a);

    const std::size_t n = a.size();
    for (std::size_t i = 0; i + 1 < n; ++i) {
        // Find index of smallest element in [i, n).
        std::size_t smallest = i;
        for (std::size_t j = i + 1; j < n; ++j) {
            if (a[j] < a[smallest]) smallest = j;
        }
        // Park it at position i.
        std::swap(a[i], a[smallest]);
    }
    print("selection:    ", a);

    // ── std::sort: one line, faster, less error-prone ───────────
    std::array<int, 6> b{ 30, 50, 20, 10, 40, 60 };
    std::sort(b.begin(), b.end());
    print("std::sort:    ", b);
}
