// 12.14 — auto strips references and top-level const. Spell out auto& / const auto&.
#include <iostream>
#include <type_traits>
#include <vector>

template <class T> constexpr bool is_ref_v   = std::is_reference_v<T>;
template <class T> constexpr bool is_const_v = std::is_const_v<std::remove_reference_t<T>>;

int main() {
    int x { 5 };
    const int cx { 10 };
    int& rx { x };
    const int& crx { cx };

    // 1) auto strips reference + top-level const → plain int copy.
    auto a1 { rx };
    a1 = 100;                       // doesn't touch x
    std::cout << "auto a1 from rx: a1=" << a1 << " x=" << x
              << "  (copy — not an alias)\n";

    // 2) auto& preserves reference (and const, if present).
    auto& a2 { rx };
    a2 = 50;                        // does touch x
    std::cout << "auto& a2 from rx: x=" << x << "  (alias — mutates x)\n";

    // 3) const auto& — read-only alias. The workhorse for inputs and for loops.
    const auto& a3 { x };
    // a3 = 0;                       // ERROR: const
    std::cout << "const auto& a3 from x: a3=" << a3 << '\n';

    // 4) Pointee const survives plain `auto`:
    const int* cp { &cx };
    auto a4 { cp };                  // deduces const int*, not int*
    static_assert(std::is_same_v<decltype(a4), const int*>);
    std::cout << "auto a4 from `const int*` → still const int*\n";

    // Range-based for: read-only loop — `const auto&` avoids copying each element.
    std::vector<std::string> words { "alpha", "beta", "gamma" };
    for (const auto& w : words) std::cout << w << ' ';
    std::cout << '\n';

    // Sanity:
    std::cout << "rx ref?   " << is_ref_v<decltype(rx)>   << '\n';
    std::cout << "a1 ref?   " << is_ref_v<decltype(a1)>   << "  (dropped)\n";
    std::cout << "a2 ref?   " << is_ref_v<decltype(a2)>   << "  (kept via auto&)\n";
    std::cout << "a3 const? " << is_const_v<decltype(a3)> << "  (kept via const auto&)\n";
    (void)crx;
}
