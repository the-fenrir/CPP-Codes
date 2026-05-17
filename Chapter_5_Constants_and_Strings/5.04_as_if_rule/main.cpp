// 5.4 — as-if rule: the compiler can fold/propagate/elide as long as
//       observable behavior is preserved. To actually *see* this, compile
//       with -O2 and look at the assembly. Behavior here is unchanged
//       either way — that's the point.
#include <iostream>

int main() {
    // Constant folding: 3 + 4 is computed at compile time.
    const int folded { 3 + 4 };
    std::cout << "folded = " << folded << '\n';

    // Constant propagation: `radius` is a const initialized from a literal,
    // so the compiler can substitute 10 into the expression below and fold
    // again. With -O2, `area` is effectively a literal in the binary.
    const int radius { 10 };
    const int area   { 3 * radius * radius };
    std::cout << "area   = " << area << '\n';

    // Dead-code elimination: `wasted` isn't observed anywhere, and computing
    // it has no side effects. The optimizer is free to delete it. Adding a
    // print of `wasted` would force the computation to happen.
    int wasted { (1 + 2) * (3 + 4) * (5 + 6) };
    (void)wasted; // suppress unused-variable warning; doesn't force computation

    // I/O is observable — the compiler cannot elide this line, even though
    // the value being printed is trivially knowable.
    std::cout << "observable: " << (1 + 2) << '\n';
}
