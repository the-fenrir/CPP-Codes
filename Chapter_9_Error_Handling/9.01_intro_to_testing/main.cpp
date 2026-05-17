// 9.1 — minimal hand-rolled unit-test harness.
// No framework, no dependencies — just a function under test and a
// table of (input, expected) pairs. This *is* a unit test: small,
// isolated, automated, and the failure message tells you what broke.
#include <iostream>
#include <string_view>

// ── Function under test ─────────────────────────────────────────
bool isPositive(int x) {
    return x > 0;
}

// ── Tiny test harness ───────────────────────────────────────────
static int g_failures = 0;

void check(std::string_view name, bool got, bool expected) {
    if (got == expected) {
        std::cout << "  PASS  " << name << '\n';
    } else {
        std::cout << "  FAIL  " << name
                  << " (got " << std::boolalpha << got
                  << ", expected " << expected << ")\n";
        ++g_failures;
    }
}

int main() {
    std::cout << "── isPositive() tests ──\n";

    // Happy path
    check("isPositive(1)",        isPositive(1),        true);
    check("isPositive(1000000)",  isPositive(1000000),  true);

    // Boundary — zero is NOT positive
    check("isPositive(0)",        isPositive(0),        false);

    // Sad path
    check("isPositive(-1)",       isPositive(-1),       false);
    check("isPositive(INT_MIN)",  isPositive(-2147483647 - 1), false);

    std::cout << '\n'
              << (g_failures == 0 ? "All tests passed.\n"
                                  : "FAILURES present.\n");
    return g_failures;
}
