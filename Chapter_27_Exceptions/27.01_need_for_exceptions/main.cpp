// 27.1 — three ways to signal "can't divide by zero": sentinel, out-param, exception.
#include <iostream>
#include <limits>
#include <optional>
#include <stdexcept>

// ── (1) sentinel return value ──────────────────────────────────────
// Caller MUST remember to check for the sentinel. Easy to forget.
// Also: NaN is a valid double in some contexts, so the sentinel collides with reality.
double divide_sentinel(int a, int b) {
    if (b == 0) return std::numeric_limits<double>::quiet_NaN();
    return static_cast<double>(a) / b;
}

// ── (2) std::optional return ───────────────────────────────────────
// Better than a sentinel: failure is in the type system. But still no
// information about *why* it failed, and every caller must unwrap it.
std::optional<double> divide_opt(int a, int b) {
    if (b == 0) return std::nullopt;
    return static_cast<double>(a) / b;
}

// ── (3) exception ──────────────────────────────────────────────────
// The function signature is now honest: "this returns a double, or it fails."
// Failure carries a message and traverses the stack on its own.
double divide_exc(int a, int b) {
    if (b == 0) throw std::runtime_error{ "division by zero" };
    return static_cast<double>(a) / b;
}

int main() {
    // (1) sentinel — easy to forget the check
    double r1 = divide_sentinel(10, 0);
    if (r1 != r1) std::cout << "[sentinel]  divide failed (NaN)\n"; // NaN != NaN trick
    else          std::cout << "[sentinel]  result=" << r1 << '\n';

    // (2) optional — failure is in the type
    if (auto r2 = divide_opt(10, 0); r2) std::cout << "[optional]  result=" << *r2 << '\n';
    else                                  std::cout << "[optional]  divide failed\n";

    // (3) exception — failure carries a message, can't be silently ignored
    try {
        double r3 = divide_exc(10, 0);
        std::cout << "[exception] result=" << r3 << '\n';
    } catch (const std::exception& e) {
        std::cout << "[exception] divide failed: " << e.what() << '\n';
    }

    return 0;
}
