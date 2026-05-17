// 4.8 — float vs double, setprecision, rounding error, Inf/NaN.
#include <cmath>      // std::isnan, std::sqrt
#include <iomanip>    // std::setprecision
#include <iostream>

int main() {
    std::cout << "── sizes ──\n";
    std::cout << "float       : " << sizeof(float)       << " byte(s)\n";
    std::cout << "double      : " << sizeof(double)      << " byte(s)\n";
    std::cout << "long double : " << sizeof(long double) << " byte(s)\n";

    std::cout << "\n── default vs setprecision ──\n";
    double pi{ 3.14159265358979 };
    std::cout << "default   : " << pi << '\n';                 // 6 sig figs default
    std::cout << std::setprecision(16);
    std::cout << "setprec16 : " << pi << '\n';                 // shows the rest

    std::cout << "\n── rounding error: 0.1 + 0.2 ≠ 0.3 ──\n";
    double a{ 0.1 };
    double b{ 0.2 };
    double sum{ a + b };
    std::cout << "0.1 + 0.2 = " << sum << '\n';
    std::cout << "(sum == 0.3) = " << std::boolalpha << (sum == 0.3) << '\n';

    std::cout << "\n── Inf and NaN ──\n";
    double inf { 1.0 / 0.0 };          // +Inf (well-defined for double)
    double nan { std::sqrt(-1.0) };    // NaN
    std::cout << "1.0 / 0.0    = " << inf << '\n';
    std::cout << "sqrt(-1.0)   = " << nan << '\n';
    std::cout << "NaN == NaN   = " << (nan == nan)     << '\n';   // false
    std::cout << "isnan(NaN)   = " << std::isnan(nan)  << '\n';   // true
}
