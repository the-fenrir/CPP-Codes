// 16.9 — index a vector by enumerators; sentinel guards the size.
#include <cassert>
#include <iostream>
#include <string_view>
#include <vector>

namespace Items {
    enum Type {
        health_potion,
        torch,
        arrow,
        max_items   // sentinel: count of real items
    };

    constexpr std::string_view name(Type t) {
        switch (t) {
            case health_potion: return "health potion";
            case torch:         return "torch";
            case arrow:         return "arrow";
            default:            return "unknown";
        }
    }
}

int main() {
    // Inventory must have exactly `max_items` entries — one slot per enumerator.
    std::vector inventory{ 1, 5, 10 };
    assert(std::ssize(inventory) == Items::max_items
           && "inventory size out of sync with Items enum");

    // Named access: clear, self-documenting.
    std::cout << Items::name(Items::torch) << "s: "
              << inventory[Items::torch] << '\n';

    // Loop using the sentinel as the upper bound.
    int total{ 0 };
    for (int i{ 0 }; i < Items::max_items; ++i) {
        std::cout << inventory[static_cast<std::size_t>(i)]
                  << ' ' << Items::name(static_cast<Items::Type>(i)) << "(s)\n";
        total += inventory[static_cast<std::size_t>(i)];
    }
    std::cout << "total items: " << total << '\n';
}
