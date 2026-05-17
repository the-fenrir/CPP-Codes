// 4.12 — implicit conversion, brace-init narrowing rejection, static_cast.
#include <iostream>

void takesDouble(double d) {
    std::cout << "  takesDouble got: " << d << '\n';
}

int main() {
    std::cout << "── implicit conversion: int → double at call site ──\n";
    takesDouble(5);            // 5 implicitly promoted to 5.0

    std::cout << "\n── brace-init refuses narrowing ──\n";
    // int x{ 5.5 };           // compile error: narrowing conversion
    // `=` init compiles with a warning — that warning is the point of this
    // demo, so we silence it locally rather than make the example wrong.
#if defined(__clang__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wliteral-conversion"
#elif defined(__GNUC__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wconversion"
#endif
    int x = 5.5;               // compiles, drops fractional part
#if defined(__clang__)
#  pragma clang diagnostic pop
#elif defined(__GNUC__)
#  pragma GCC diagnostic pop
#endif
    std::cout << "int x = 5.5  → x = " << x << '\n';

    std::cout << "\n── static_cast: explicit truncation ──\n";
    double d{ 3.7 };
    int    i{ static_cast<int>(d) };   // 3, fractional part dropped — your call
    std::cout << "static_cast<int>(3.7) = " << i << '\n';

    std::cout << "\n── static_cast<int> to print a char's numeric value ──\n";
    char ch{ 'A' };
    std::cout << "ch as char : " << ch                       << '\n';   // A
    std::cout << "ch as int  : " << static_cast<int>(ch)     << '\n';   // 65
}
