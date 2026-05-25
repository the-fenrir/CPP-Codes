// 17.6 — parallel std::arrays indexed by an unscoped enum.
#include <array>
#include <iostream>
#include <string_view>

namespace Potion {
    enum Type {
        healing,
        mana,
        speed,
        invisibility,
        max_potions,    // sentinel — length lives here
    };

    constexpr std::array<std::string_view, max_potions> name {
        "healing", "mana", "speed", "invisibility"
    };
    constexpr std::array<int, max_potions> cost {
        20, 30, 12, 50
    };
    constexpr std::array<int, max_potions> weight {
        1, 2, 1, 3
    };

    // Guardrails: if someone adds a new enumerator they MUST extend each array.
    static_assert(std::size(name)   == max_potions);
    static_assert(std::size(cost)   == max_potions);
    static_assert(std::size(weight) == max_potions);
}

int main() {
    using namespace Potion;

    // Indexing by enumerator — readable, type-checked (sort of).
    std::cout << name[healing] << " costs " << cost[healing]
              << ", weighs " << weight[healing] << '\n';

    // Loop over every potion via the sentinel.
    for (int p { 0 }; p < max_potions; ++p)
        std::cout << p << ") " << name[p] << " — " << cost[p] << " gp\n";
}
