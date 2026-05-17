// 8.11 — break and continue, and the while+continue increment trap.
#include <array>
#include <iostream>

int main() {
    constexpr std::array<int, 8> data{ 4, 1, 9, -3, 7, 0, 12, 5 };

    // ── break: stop on first match ──
    int target{ 9 };
    int foundAt{ -1 };
    for (int i{ 0 }; i < static_cast<int>(data.size()); ++i) {
        if (data[i] == target) {
            foundAt = i;
            break;                       // exit the for; rest of array ignored
        }
    }
    std::cout << "found " << target << " at index " << foundAt << '\n';

    // ── continue: skip negatives, sum the rest ──
    int sum{ 0 };
    for (int v : data) {
        if (v < 0) continue;             // skip; `for` step still runs
        sum += v;
    }
    std::cout << "sum of non-negative = " << sum << '\n';

    // ── While + continue trap (shown commented; uncommenting would hang) ──
    //   int i = 0;
    //   while (i < 5) {
    //       if (i == 2) continue;       // i never increments → infinite loop
    //       std::cout << i;
    //       ++i;
    //   }

    // ── Nested loop: `break` exits only the inner loop ──
    for (int r{ 0 }; r < 3; ++r) {
        for (int c{ 0 }; c < 4; ++c) {
            if (c == r) break;           // exit inner only
            std::cout << '(' << r << ',' << c << ") ";
        }
    }
    std::cout << '\n';
}
