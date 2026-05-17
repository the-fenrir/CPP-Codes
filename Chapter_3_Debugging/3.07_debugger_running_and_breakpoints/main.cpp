// 3.7 — practice breakpoints and conditional breakpoints.
//
// binarySearchBuggy has a subtle off-by-one: on the not-found path, the loop
// can become infinite for certain inputs. (Mitigated here with a max iteration
// guard so the program terminates.)
//
//   lldb build/3.07/main
//   (lldb) b binarySearchBuggy           # break each call
//   (lldb) breakpoint set -f main.cpp -l 22 -c 'target == 42'
//                                         # break only on the not-found case
//   (lldb) run
//   (lldb) c                             # continue; next break is the bad call
#include <iostream>
#include <vector>

// Returns index of target, or -1 if not present. Buggy: uses `<` in the loop
// condition but doesn't move `low` past `mid` correctly when not found.
int binarySearchBuggy(const std::vector<int>& v, int target) {
    int low{ 0 };
    int high{ static_cast<int>(v.size()) - 1 };
    int guard{ 0 };
    while (low <= high) {
        if (++guard > 64) return -2;           // safety: detect infinite loop
        int mid{ (low + high) / 2 };
        if (v[mid] == target) return mid;
        if (v[mid] < target) low = mid;        // BUG: should be `mid + 1`
        else                 high = mid - 1;
    }
    return -1;
}

int binarySearchFixed(const std::vector<int>& v, int target) {
    int low{ 0 };
    int high{ static_cast<int>(v.size()) - 1 };
    while (low <= high) {
        int mid{ (low + high) / 2 };
        if (v[mid] == target) return mid;
        if (v[mid] < target) low = mid + 1;
        else                 high = mid - 1;
    }
    return -1;
}

int main() {
    std::vector<int> v{ 1, 3, 7, 15, 31, 63 };
    for (int t : { 7, 42, 1, 63 }) {
        std::cout << "buggy(" << t << ") = " << binarySearchBuggy(v, t)
                  << "   fixed = " << binarySearchFixed(v, t) << '\n';
    }
    // buggy(42) returns -2: the guard catches the infinite loop. This is the
    // case to set the conditional breakpoint on.
}
