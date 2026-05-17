// 4.5 — three concrete unsigned-integer footguns.
#include <iostream>

void takesUnsigned(unsigned int n) {
    std::cout << "  takesUnsigned got: " << n << '\n';
}

int main() {
    // 1. Wrap-around on underflow.
    unsigned int u{ 0 };
    --u;
    std::cout << "0u - 1 = " << u << "  (wraps to UINT_MAX, not -1)\n";

    // 2. Wrap-around on overflow.
    unsigned char c{ 250 };
    c = static_cast<unsigned char>(c + 10);  // 260 mod 256 = 4
    std::cout << "250 + 10 as unsigned char = " << static_cast<int>(c) << '\n';

    // 3. Mixed signed/unsigned comparison.
    //    -1 is converted to unsigned (a huge value), so the comparison is FALSE.
    //    We deliberately trigger the comparison to demonstrate the bug — the
    //    compiler's -Wsign-compare warning *is the lesson*, so we silence it
    //    locally rather than fix the "bug".
    int  s{ -1 };
    unsigned int t{ 1 };
#if defined(__clang__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wsign-compare"
#elif defined(__GNUC__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wsign-compare"
#endif
    std::cout << "(-1 < 1u) = " << std::boolalpha << (s < t) << '\n';
#if defined(__clang__)
#  pragma clang diagnostic pop
#elif defined(__GNUC__)
#  pragma GCC diagnostic pop
#endif

    // 4. Passing a negative literal to an unsigned parameter.
    //    Compiles (with a warning under -Wconversion). Silently becomes huge.
    takesUnsigned(static_cast<unsigned int>(-1));
}
