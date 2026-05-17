// 3.4 — print-debugging in action.
//
// `countEven` should return the count of even numbers in the vector.
// On input {2, 4, 6, 7, 8} it returns 3 — should be 4. We find out why by
// adding [DBG] prints at the loop boundary and inside the branch.
#include <iostream>
#include <vector>

int countEven(const std::vector<int>& v) {
    int count{ 0 };
    std::cerr << "[DBG] entering countEven, size=" << v.size() << '\n';

    for (std::size_t i{ 0 }; i < v.size(); ++i) {
        std::cerr << "[DBG] i=" << i << " v[i]=" << v[i] << '\n';
        if (v[i] % 2 == 0) {
            ++count;
            std::cerr << "[DBG]   even — count now " << count << '\n';
            break;                // BUG: should be `continue`, not `break`.
        }
    }

    std::cerr << "[DBG] returning " << count << '\n';
    return count;
}

int main() {
    std::vector<int> v{ 2, 4, 6, 7, 8 };
    std::cout << "count = " << countEven(v) << "  (expect 4)\n";

    // The [DBG] trace makes the bug obvious: we exit the loop after the first
    // even, because `break` short-circuits the whole search. Replace `break`
    // with `continue` (or just remove it) and the count is correct.
    //
    // To run with debug output suppressed:   ./main 2>/dev/null
    // To capture only debug output:          ./main 2>trace.log
}
