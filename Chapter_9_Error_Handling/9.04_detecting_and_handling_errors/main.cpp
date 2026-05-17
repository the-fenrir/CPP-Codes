// 9.4 — three error-handling strategies for one function.
// Precondition for all three: `denominator != 0`.
#include <iostream>
#include <optional>

// ── Strategy 1: silent default ──────────────────────────────────
// Caller has no way to know the precondition failed. Use only when
// the default is genuinely correct for every caller (rarely).
int divide_silent(int a, int b) {
    if (b == 0) return 0;          // <- pretends nothing happened
    return a / b;
}

// ── Strategy 2: return std::optional ────────────────────────────
// Caller is forced to inspect the result. Recommended default in
// modern C++ when the error is recoverable.
std::optional<int> divide_optional(int a, int b) {
    if (b == 0) return std::nullopt;
    return a / b;
}

// ── Strategy 3: abort on precondition violation ─────────────────
// For *non-recoverable* states only (this isn't really one; we use
// it here for demonstration). Note we write to std::cerr, not cout.
int divide_or_abort(int a, int b) {
    if (b == 0) {
        std::cerr << "divide_or_abort: precondition b!=0 violated\n";
        std::abort();
    }
    return a / b;
}

int main() {
    std::cout << "── strategy 1: silent default ──\n";
    std::cout << "10/2 = " << divide_silent(10, 2) << '\n';
    std::cout << "10/0 = " << divide_silent(10, 0) << "   <-- pretends 0 is the answer\n";

    std::cout << "\n── strategy 2: std::optional ──\n";
    if (auto r = divide_optional(10, 2)) std::cout << "10/2 = " << *r << '\n';
    if (!divide_optional(10, 0))         std::cout << "10/0 -> nullopt (caller must handle)\n";

    std::cout << "\n── strategy 3: abort ──\n";
    std::cout << "10/2 = " << divide_or_abort(10, 2) << '\n';
    std::cout << "(skipping 10/0 case so the program runs to completion)\n";
}
