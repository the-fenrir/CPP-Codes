// 4.9 — bool basics: boolalpha, int→bool conversion, logical operators.
#include <iostream>

int main() {
    bool t{ true };
    bool f{ false };

    std::cout << "── default formatting ──\n";
    std::cout << "true  : " << t << '\n';   // 1
    std::cout << "false : " << f << '\n';   // 0

    std::cout << "\n── std::boolalpha (sticky) ──\n";
    std::cout << std::boolalpha;
    std::cout << "true  : " << t << '\n';   // true
    std::cout << "false : " << f << '\n';   // false

    std::cout << "\n── int → bool: 0 = false, anything else = true ──\n";
    bool b1 = 0;       // false
    bool b2 = 1;       // true
    bool b3 = -42;     // true (non-zero)
    std::cout << "bool(0)   = " << b1 << '\n';
    std::cout << "bool(1)   = " << b2 << '\n';
    std::cout << "bool(-42) = " << b3 << '\n';

    std::cout << "\n── logical operators ──\n";
    std::cout << "!true        = " << !t          << '\n';
    std::cout << "true && false = " << (t && f)   << '\n';
    std::cout << "true || false = " << (t || f)   << '\n';
}
