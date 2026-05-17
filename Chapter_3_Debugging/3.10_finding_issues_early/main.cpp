// 3.10 — defensive programming + compile-time checks.
//
// Three lines of defense, cheapest first:
//   1. static_assert — checked at compile time, free at runtime.
//   2. assert        — checked in debug builds, removed in release (NDEBUG).
//   3. throw         — checked always, survives release.
#include <cassert>
#include <iostream>
#include <limits>
#include <stdexcept>

// Compile-time invariant: int must be at least 32 bits for the rest of this
// program to mean what we think. Fails to compile on a hypothetical 16-bit
// platform — bug caught before the program even runs.
static_assert(std::numeric_limits<int>::digits >= 31,
              "this program assumes int is at least 32-bit");

// Defensive: validate inputs, fail loudly on the impossible.
int safeDivide(int a, int b) {
    // Runtime check that must survive release builds (data-dependent):
    if (b == 0)
        throw std::invalid_argument{ "safeDivide: divisor must be non-zero" };

    // Internal invariant — should never be violated by a well-formed caller.
    // assert() makes it a compile-time-only check (free in release):
    assert(b != 0 && "post-validation invariant"); // belt + suspenders

    return a / b;
}

int main() {
    std::cout << "10 / 2 = " << safeDivide(10, 2) << '\n';
    std::cout << "10 / 3 = " << safeDivide(10, 3) << '\n';

    try {
        std::cout << safeDivide(10, 0) << '\n';
    } catch (const std::invalid_argument& e) {
        std::cerr << "caught: " << e.what() << '\n';
    }

    // To see the assertion fire on a debug build, temporarily change the
    // `if (b == 0) throw` line above to a no-op, then call safeDivide(10, 0).
    // To see the static_assert fail, change `>= 31` to `>= 1000` and rebuild.
}
