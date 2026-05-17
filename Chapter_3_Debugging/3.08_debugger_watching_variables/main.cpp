// 3.8 — watch variables as they change.
//
// Computes the sum AND product of the elements of `v`. Product is wrong
// because it's initialized to 0 (not 1). Use a debugger to watch both
// running totals tick:
//
//   lldb build/3.08/main
//   (lldb) b main.cpp:18           # the start of the loop body
//   (lldb) run
//   (lldb) display sum
//   (lldb) display product
//   (lldb) c                       # each continue advances one iteration
//
// You'll see `product` stuck at 0 from the first iteration — the bug.
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{ 2, 3, 5, 7 };

    int sum{ 0 };
    int product{ 0 };               // BUG: should be 1 — anything * 0 == 0

    for (int x : v) {
        sum     += x;
        product *= x;
    }

    std::cout << "sum     = " << sum     << "  (expect 17)\n";
    std::cout << "product = " << product << "  (expect 210)\n";

    // Fixed version, side-by-side:
    int sumF{ 0 };
    int productF{ 1 };              // identity for multiplication
    for (int x : v) { sumF += x; productF *= x; }
    std::cout << "fixed sum     = " << sumF     << '\n';
    std::cout << "fixed product = " << productF << '\n';
}
