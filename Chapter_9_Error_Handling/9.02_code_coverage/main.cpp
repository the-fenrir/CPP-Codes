// 9.2 — code coverage: statement / branch / loop coverage.
//
// classify() has three branches; we hit all three.
// sumTo() is a loop; we hit it with 0, 1, and 2+ iterations.
#include <iostream>
#include <string_view>

// ── Functions under test ────────────────────────────────────────
std::string_view classify(int n) {
    if (n < 0)  return "negative";     // branch A
    if (n == 0) return "zero";         // branch B
    return "positive";                 // branch C (implicit else)
}

int sumTo(int n) {
    int s = 0;
    for (int i = 1; i <= n; ++i) s += i;
    return s;
}

// ── Harness ─────────────────────────────────────────────────────
static int g_failures = 0;

template <typename T>
void check(std::string_view name, const T& got, const T& expected) {
    if (got == expected) {
        std::cout << "  PASS  " << name << '\n';
    } else {
        std::cout << "  FAIL  " << name << '\n';
        ++g_failures;
    }
}

int main() {
    std::cout << "── classify(): branch coverage ──\n";
    check<std::string_view>("classify(-1)", classify(-1), "negative"); // branch A
    check<std::string_view>("classify(0)",  classify(0),  "zero");     // branch B
    check<std::string_view>("classify(1)",  classify(1),  "positive"); // branch C

    std::cout << "\n── sumTo(): loop coverage (0, 1, 2) ──\n";
    check("sumTo(0)", sumTo(0), 0);   // 0 iterations
    check("sumTo(1)", sumTo(1), 1);   // 1 iteration
    check("sumTo(4)", sumTo(4), 10);  // 2+ iterations

    std::cout << '\n'
              << (g_failures == 0 ? "All tests passed.\n"
                                  : "FAILURES present.\n");
    return g_failures;
}
