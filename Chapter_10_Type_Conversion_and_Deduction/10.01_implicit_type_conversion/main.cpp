// 10.1 — implicit conversions inserted by the compiler at four different sites.
#include <iostream>

void takesDouble(double d) {
    std::cout << "takesDouble got " << d << '\n';
}

int returnsLong() {
    long n = 42;
    return n;   // long -> int on return; here the value fits, so it's silent.
}

int main() {
    // Site 1: initialization. int -> double, widening (safe).
    double a = 5;
    std::cout << "a = " << a << '\n';

    // Site 2: assignment. char -> int (integral promotion). Safe.
    int b = 0;
    char c = 'A';
    b = c;
    std::cout << "b after `b = 'A'` = " << b << "  (got " << static_cast<int>('A') << ")\n";

    // Site 3: function argument. int -> double.
    takesDouble(42);

    // Site 4: return statement (see returnsLong above).
    std::cout << "returnsLong() = " << returnsLong() << '\n';

    // Site 5: condition. int -> bool (nonzero -> true).
    int n = 7;
    if (n) std::cout << "n is truthy\n";

    // Bonus: narrowing happens silently with `=`-init too. Don't rely on this.
    // Use brace init (see 10.04) when you want the compiler to catch it.
    int truncated = static_cast<int>(3.9);
    std::cout << "static_cast<int>(3.9) = " << truncated << '\n';
}
