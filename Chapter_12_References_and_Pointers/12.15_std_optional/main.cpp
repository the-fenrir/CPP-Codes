// 12.15 — std::optional: a value-or-nothing wrapper.
#include <iostream>
#include <optional>
#include <string>

// "Try" idiom: parse an int from a string, return empty on failure.
std::optional<int> tryParseInt(const std::string& s) {
    try {
        size_t pos{};
        int v = std::stoi(s, &pos);
        if (pos != s.size()) return std::nullopt;   // trailing garbage
        return v;
    } catch (...) {
        return std::nullopt;
    }
}

int main() {
    auto good = tryParseInt("42");
    auto bad  = tryParseInt("nope");
    auto trail= tryParseInt("12x");

    // Check + access:
    if (good) std::cout << "good = " << *good << '\n';
    else      std::cout << "good is empty\n";

    if (!bad) std::cout << "bad is empty (parse failed)\n";

    // value_or — supply a default for the empty case:
    std::cout << "trail.value_or(-1) = " << trail.value_or(-1) << '\n';

    // value() throws on empty — only use when emptiness is an invariant violation:
    try {
        std::cout << bad.value() << '\n';
    } catch (const std::bad_optional_access& e) {
        std::cout << "bad.value() threw: " << e.what() << '\n';
    }

    // Mutate / reset:
    std::optional<std::string> name { "Anjaneya" };
    std::cout << "name = " << *name << '\n';
    name.reset();                           // equivalent to: name = std::nullopt;
    std::cout << "after reset, name engaged? " << name.has_value() << '\n';

    // The value lives inside the optional — no heap allocation:
    std::cout << "sizeof(optional<int>) = " << sizeof(std::optional<int>) << '\n';
    std::cout << "sizeof(int)           = " << sizeof(int) << '\n';
}
