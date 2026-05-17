// 10.5 — usual arithmetic conversions: how mixed-type expressions pick a common type.
#include <iostream>
#include <typeinfo>

template <typename T>
const char* tn(const T&) { return typeid(T).name(); }

int main() {
    int    i = 5;
    double d = 2.0;

    // int + double -> double (higher on the ladder wins).
    auto sum = i + d;
    std::cout << "int + double = " << sum << "  (type " << tn(sum) << ")\n";

    // int / int = int. The fraction is discarded.
    std::cout << "5 / 2   = " << (5 / 2)   << "  (integer division)\n";
    std::cout << "5 / 2.0 = " << (5 / 2.0) << "  (one FP operand promotes both)\n";

    // The classic int-average bug.
    int a = 7, b = 4;
    double bad  = (a + b) / 2;            // (11)/2 = 5  -- integer division, then widened
    double good = (a + b) / 2.0;          // 11 / 2.0 = 5.5
    std::cout << "avg bad  = " << bad  << '\n';
    std::cout << "avg good = " << good << '\n';

    // signed vs unsigned: signed converts to unsigned, becomes huge.
    // We hide the comparison behind a function to silence -Wsign-compare;
    // the point of the lesson IS the unexpected result, not the warning.
    auto cmp = [](int x, unsigned y) {
        return static_cast<unsigned>(x) < y;   // mirrors the conversion the compiler would do
    };
    std::cout << std::boolalpha;
    std::cout << "(-1 < 1u) = " << cmp(-1, 1u) << "  (expected true, got false)\n";

    // Two narrow integer types promote to int first.
    short s1 = 10, s2 = 20;
    auto product = s1 * s2;
    std::cout << "short * short -> type " << tn(product)
              << ", value " << product << '\n';
}
