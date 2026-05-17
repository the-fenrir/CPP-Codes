// 3.3 — practice the binary-search bug hunt.
//
// findMax should return the largest element. Try it on:
//   {3, 1, 4, 1, 5, 9, 2, 6}   → expect 9
//   {-3, -1, -7}               → expect -1
// One of these fails. Find which, then narrow down the bug by adding prints
// at: (a) function entry, (b) inside the loop, (c) before return.
#include <iostream>
#include <vector>

int findMaxBuggy(const std::vector<int>& v) {
    int max{ 0 };                   // BUG: assumes a non-negative element exists
    for (int x : v)
        if (x > max) max = x;
    return max;
}

int findMaxFixed(const std::vector<int>& v) {
    int max{ v.at(0) };             // start from the first element, not zero
    for (int x : v)
        if (x > max) max = x;
    return max;
}

int main() {
    std::vector<int> pos{ 3, 1, 4, 1, 5, 9, 2, 6 };
    std::vector<int> neg{ -3, -1, -7 };

    std::cout << "buggy(pos) = " << findMaxBuggy(pos) << "  (expect 9)\n";
    std::cout << "buggy(neg) = " << findMaxBuggy(neg) << "  (expect -1)\n";
    std::cout << "fixed(pos) = " << findMaxFixed(pos) << "  (expect 9)\n";
    std::cout << "fixed(neg) = " << findMaxFixed(neg) << "  (expect -1)\n";
}
