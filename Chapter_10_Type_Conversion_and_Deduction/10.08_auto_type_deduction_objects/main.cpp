// 10.8 — `auto` deduces the variable type from its initializer.
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

template <typename T>
const char* tn(const T&) { return typeid(T).name(); }

int main() {
    auto i = 5;         // int
    auto u = 5u;        // unsigned int
    auto d = 5.0;       // double
    auto f = 5.0f;      // float
    auto s = std::string{ "hi" };

    std::cout << "i type=" << tn(i) << " val=" << i << '\n';
    std::cout << "u type=" << tn(u) << " val=" << u << '\n';
    std::cout << "d type=" << tn(d) << " val=" << d << '\n';
    std::cout << "f type=" << tn(f) << " val=" << f << '\n';
    std::cout << "s type=" << tn(s) << " val=" << s << '\n';

    // const + reference variants.
    int n = 10;
    const auto  copy   = n;    // int  (top-level const goes on the alias, value is copied)
    auto&       ref    = n;    // int&
    const auto& cref   = n;    // const int&

    ref = 11;                  // mutates n through ref
    std::cout << "n=" << n << " copy=" << copy << " cref=" << cref << '\n';

    // Range-for: copy vs. const-ref.
    std::vector<std::string> names{ "alice", "bob", "carol" };
    for (auto x : names) x += "!";              // mutates a copy; original unchanged
    for (const auto& x : names) std::cout << x << ' ';
    std::cout << '\n';
}
