// 10.3 — numeric conversions: when the compiler quietly drops information.
#include <iostream>

int main() {
    // (1) Integer -> narrower integer (truncates high bits).
    int big = 300;
    char small = static_cast<char>(big);  // 300 doesn't fit in a signed char
    std::cout << "int 300 -> char: " << static_cast<int>(small) << '\n';

    // (2) double -> float (loses precision).
    double d = 3.141592653589793;
    float  f = static_cast<float>(d);
    std::cout << "double pi as float: " << f << '\n';

    // (3) FP -> integer: truncation toward zero.
    int a = static_cast<int>( 3.9);  // -> 3
    int b = static_cast<int>(-3.9);  // -> -3, not -4
    std::cout << "trunc( 3.9) = " << a << ",  trunc(-3.9) = " << b << '\n';

    // (4) Integer -> FP: usually fine, but very large ints aren't exactly representable.
    int    huge = 16777217;       // 2^24 + 1
    float  hf   = static_cast<float>(huge);
    std::cout << "int " << huge << " as float = " << hf << "  (lost the +1)\n";

    // (5) Numeric -> bool.
    std::cout << "bool(0)  = " << static_cast<bool>(0)  << '\n';
    std::cout << "bool(42) = " << static_cast<bool>(42) << '\n';

    // Bonus: signed -> unsigned of negative wraps mod 2^N. Defined, almost never desired.
    unsigned u = static_cast<unsigned>(-1);
    std::cout << "unsigned(-1) = " << u << '\n';
}
