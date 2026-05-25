// 16.6 — index loops for sum, find-first, and min-index.
#include <iostream>
#include <vector>

int main() {
    std::vector v{ 7, 2, 9, 4, 5, 9, 1, 8 };

    // Sum.
    int sum{ 0 };
    for (std::size_t i{ 0 }; i < v.size(); ++i) sum += v[i];
    std::cout << "sum = " << sum << '\n';

    // Find-first: index of the first 9, or -1 if none.
    int firstNine{ -1 };
    for (std::size_t i{ 0 }; i < v.size(); ++i) {
        if (v[i] == 9) { firstNine = static_cast<int>(i); break; }
    }
    std::cout << "first 9 at index " << firstNine << '\n';

    // Min index — assumes v is non-empty.
    std::size_t minIdx{ 0 };
    for (std::size_t i{ 1 }; i < v.size(); ++i) {
        if (v[i] < v[minIdx]) minIdx = i;
    }
    std::cout << "min " << v[minIdx] << " at index " << minIdx << '\n';
}
