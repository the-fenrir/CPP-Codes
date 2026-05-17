// 9.6 — assert (runtime) and static_assert (compile time).
//
// All asserts here HOLD by construction. The *would-fail* examples
// are kept inert (inside `if (false) { ... }`) so the program runs
// to completion — flip the condition or remove the guard to see
// them fire.
#include <cassert>
#include <iostream>
#include <type_traits>

// ── static_assert (compile-time) ────────────────────────────────
static_assert(sizeof(int) >= 4,
              "this code assumes int is at least 32-bit");
static_assert(2 + 2 == 4,
              "fundamental arithmetic broken");

// Constexpr function exercised by static_assert
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}
static_assert(factorial(5) == 120,
              "factorial implementation is wrong");

// ── A function with an asserted precondition ────────────────────
int firstElement(const int* arr, int len) {
    assert(arr != nullptr && "arr must not be null");
    assert(len > 0          && "len must be positive");
    return arr[0];
}

// ── Template constrained by static_assert ───────────────────────
template <typename T>
T doubled(T x) {
    static_assert(std::is_arithmetic_v<T>,
                  "doubled() requires an arithmetic type");
    return x + x;
}

int main() {
    std::cout << "── static_assert: all passed at compile time ──\n";
    std::cout << "  factorial(5) = " << factorial(5) << " (verified at compile time)\n";

    std::cout << "\n── runtime asserts (all hold) ──\n";
    const int data[]{ 10, 20, 30 };
    const int first = firstElement(data, 3);
    std::cout << "  firstElement(data, 3) = " << first << '\n';

    std::cout << "  doubled(3.5) = " << doubled(3.5) << '\n';
    std::cout << "  doubled(7)   = " << doubled(7)   << '\n';

    // ── Would-fire examples (kept inert) ───────────────────────
    if (false) {
        // assert(false && "unreachable: this branch shouldn't run");
        // firstElement(nullptr, 1);        // would fire arr != nullptr
        // firstElement(data, 0);           // would fire len > 0
        // doubled(std::string{"hi"});      // would fire static_assert at compile time
    }
    std::cout << "\n(would-fail cases are guarded; see source.)\n";
}
