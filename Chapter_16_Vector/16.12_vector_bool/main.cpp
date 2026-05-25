// 16.12 — vector<bool> is a bit-packed specialization; subscript returns a proxy.
#include <iostream>
#include <type_traits>
#include <vector>

int main() {
    std::vector<bool> flags{ true, false, true, true, false };

    // Looks fine: print every flag.
    std::cout << "flags: ";
    for (bool b : flags) std::cout << b << ' ';
    std::cout << '\n';

    // Subscript returns a proxy. `auto` deduces the proxy, NOT `bool`.
    auto x{ flags[0] };
    bool y{ flags[0] };
    std::cout << "auto x is bool? " << std::boolalpha
              << std::is_same_v<decltype(x), bool> << '\n';
    std::cout << "bool y is bool? "
              << std::is_same_v<decltype(y), bool> << '\n';

    // Mutating through the proxy DOES work — that's the polite half of the design.
    flags[1] = true;
    std::cout << "flags[1] now " << flags[1] << '\n';

    // What you CAN'T do: &flags[0] is not a bool*.
    // bool* p = &flags[0];   // would not compile

    // Prefer this for an honest array of flags:
    std::vector<char> realFlags{ 1, 0, 1, 1, 0 };
    std::cout << "realFlags: ";
    for (char c : realFlags) std::cout << static_cast<int>(c) << ' ';
    std::cout << '\n';
}
