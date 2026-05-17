// 7.9 — `inline` = "may be defined in multiple TUs; linker picks one".
// In a single-TU demo there's no link-time effect to see, so the more
// important examples live in 7.10 (multi-file). Here we just exercise
// the syntax: inline function and inline constexpr variable.
#include <iostream>

// Inline free function — multiple TUs may define it; linker treats as one.
inline int square(int x) { return x * x; }

// constexpr functions are *implicitly* inline (no need to spell it).
constexpr int cube(int x) { return x * x * x; }

// Inline constexpr variable — the canonical "shared constant" form.
inline constexpr double pi{ 3.14159265358979323846 };

int main() {
    std::cout << "square(5) = " << square(5) << '\n';
    std::cout << "cube(3)   = " << cube(3)   << '\n';
    std::cout << "pi        = " << pi        << '\n';

    static_assert(cube(4) == 64, "constexpr function usable at compile time");
    static_assert(pi > 3.0,      "inline constexpr var usable at compile time");
}
