// Chapter 7 quiz solutions.
//   Q1: dangling-statement bug fix (blocks).
//   Q2: constants.h via inline constexpr — inlined here as a namespace
//       so this file remains a single self-contained TU.
//   Q3: accumulate() using a static local.
//   Q3b: discussion — see NOTES.md.
#include <iostream>
#include <sstream>

// ── Q1: fix the dangling-statement bug ──────────────────────────────────
//
// Design note:
//   The original code's `if` body was just the print; `num = -num;` ran
//   regardless. The fix is a block — the cheapest, most local solution.
//   Don't restructure the function; just add the `{ }`. We accept `num`
//   as a parameter here so the function is testable without stdin.
int absify_q1(int num) {
    if (num < 0) {
        // (in the original program this also prints; omitted here so the
        //  function is pure for the demo)
        num = -num;
    }
    return num;
}

// ── Q2: constants.h replacement ─────────────────────────────────────────
//
// Design note:
//   In a real project this lives in `constants.h`:
//
//     #pragma once
//     namespace Constants {
//         inline constexpr int maxClassSize{ 35 };
//     }
//
//   `inline` → safe to include from any number of TUs, one shared entity.
//   `constexpr` → compile-time, usable in static_assert / array sizes.
//   Wrapped in `namespace Constants` so the name doesn't pollute the
//   global namespace.
namespace Constants {
    inline constexpr int maxClassSize{ 35 };
}

void q2_demo(int students) {
    if (students > Constants::maxClassSize)
        std::cout << "  " << students << " students: too many\n";
    else
        std::cout << "  " << students << " students: ok\n";
}

// ── Q3: accumulate() with a static local ────────────────────────────────
//
// Design notes:
//   • A `static int s_sum{ 0 };` inside the function is the textbook use
//     case for 7.11: function-private state that persists across calls.
//   • Initialized once on first entry; ++/+= every call afterward.
//   • Shortcomings (Q3b discussion in NOTES.md):
//       1. Hidden state — depends on call history; untestable in isolation.
//       2. Only one running total ever; can't have two independent sums.
//   A class-based alternative would solve both.
int accumulate(int x) {
    static int s_sum{ 0 };
    s_sum += x;
    return s_sum;
}

int main() {
    std::cout << "── Q1: absify ──\n";
    std::cout << "  absify_q1(-5) = " << absify_q1(-5) << "  (expected 5)\n";
    std::cout << "  absify_q1( 7) = " << absify_q1( 7) << "  (expected 7)\n";

    std::cout << "\n── Q2: Constants::maxClassSize ──\n";
    static_assert(Constants::maxClassSize == 35);
    q2_demo(20);
    q2_demo(50);

    std::cout << "\n── Q3: accumulate ──\n";
    std::cout << "  accumulate(4) = " << accumulate(4) << "  (expected 4)\n";
    std::cout << "  accumulate(3) = " << accumulate(3) << "  (expected 7)\n";
    std::cout << "  accumulate(2) = " << accumulate(2) << "  (expected 9)\n";
    std::cout << "  accumulate(1) = " << accumulate(1) << "  (expected 10)\n";
}
