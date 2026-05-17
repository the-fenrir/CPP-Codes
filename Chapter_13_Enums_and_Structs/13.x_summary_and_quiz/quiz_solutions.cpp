// Chapter 13 quiz solutions.
//   Q1: Monster struct + printMonster()
//   Q2: discussion — see NOTES.md
//   Q3: Triad class template + print() using CTAD
#include <iostream>
#include <string>
#include <string_view>

// ── Q1: Monster ─────────────────────────────────────────────────────
//
// Design notes:
//  • `Type` is a scoped enum — no enumerator leakage and the type system
//    distinguishes Monster types from any other enum's values. Default for
//    new enums in modern code.
//  • A small `name(Type)` helper returns std::string_view over literals —
//    no allocation, no dangling, switch over all enumerators so the compiler
//    will warn if a new one is added without a print branch.
//  • `printMonster` takes a `const Monster&`. Monster contains a std::string,
//    so by-value would copy that string on every call.
struct Monster {
    enum class Type { ogre, dragon, orc, giantSpider, slime };

    Type        type{};
    std::string name{};
    int         health{ 0 };
};

constexpr std::string_view getTypeName(Monster::Type t) {
    switch (t) {
        case Monster::Type::ogre:        return "Ogre";
        case Monster::Type::dragon:      return "Dragon";
        case Monster::Type::orc:         return "Orc";
        case Monster::Type::giantSpider: return "Giant Spider";
        case Monster::Type::slime:       return "Slime";
    }
    return "Unknown";
}

void printMonster(const Monster& m) {
    std::cout << "This " << getTypeName(m.type)
              << " is named " << m.name
              << " and has " << m.health << " health.\n";
}

// ── Q3: Triad class template ────────────────────────────────────────
//
// Design notes:
//  • Three same-typed members → one template parameter.
//  • Aggregate struct: no constructors, all-public members. Aggregate init
//    + (under C++17) a deduction guide enables CTAD. Under C++20 the guide
//    isn't required, but we include it to document the intent and stay
//    portable to C++17 toolchains.
//  • `print` is a free function template, takes `const Triad<T>&` so it
//    works with any T without copying.
template <typename T>
struct Triad {
    T first;
    T second;
    T third;
};

// C++17 needs this for aggregate CTAD; C++20 does not (harmless either way).
template <typename T>
Triad(T, T, T) -> Triad<T>;

template <typename T>
void print(const Triad<T>& t) {
    std::cout << '[' << t.first << ", " << t.second << ", " << t.third << ']';
}

int main() {
    std::cout << "── Q1: Monster ──\n";
    Monster torg { Monster::Type::ogre,  "Torg",  145 };
    Monster blurp{ Monster::Type::slime, "Blurp", 23 };
    printMonster(torg);
    printMonster(blurp);

    std::cout << "\n── Q3: Triad ──\n";
    Triad t1{ 1, 2, 3 };           // CTAD → Triad<int>
    Triad t2{ 1.2, 3.4, 5.6 };     // CTAD → Triad<double>
    print(t1);
    print(t2);
    std::cout << '\n';
}
