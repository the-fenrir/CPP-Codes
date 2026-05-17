// 5.6 — constexpr: like const, but the compiler insists the initializer
//       is a constant expression. Catches "this looked compile-time but
//       wasn't" at the source.
#include <iostream>
#include <string_view>

int getInput() {
    int x{};
    std::cin >> x;
    return x;
}

int main() {
    // Plain literal types — all fine.
    constexpr int     n  { 42 };
    constexpr double  pi { 3.14159 };
    constexpr char    nl { '\n' };
    constexpr bool    on { true };

    // constexpr implies const — these reassignments are errors:
    // n = 7; pi = 0.0;

    // String constants: prefer constexpr std::string_view to a bare
    // string literal when you want a name for it. std::string itself is
    // not (reliably) a literal type, so `constexpr std::string` won't
    // compile portably.
    constexpr std::string_view greeting{ "hello, world" };

    std::cout << greeting << nl;
    std::cout << "n=" << n << " pi=" << pi << " on=" << std::boolalpha << on << '\n';

    // This is the line `constexpr` is built to reject. Uncomment to see:
    // constexpr int oops{ getInput() }; // error: initializer is not a constant expression
    (void)&getInput;
}
