// 8.15 — a program-wide random source. Mirrors the site's Random.h shape,
//        inlined so this folder builds standalone.
#include <iostream>
#include <random>

// ── "Random.h" equivalent, inlined ─────────────────────────────────────────
//   In a real project this whole namespace would live in Random.h and be
//   #included by anything that needs randomness. `inline` on the engine makes
//   it a single program-wide instance even if the header is included from
//   multiple translation units.
namespace Random {

    // One engine for the whole program, seeded once.
    inline std::mt19937 mt{ std::random_device{}() };

    // Uniform int in [min, max], both inclusive.
    inline int get(int min, int max) {
        std::uniform_int_distribution<int> dist{ min, max };
        return dist(mt);
    }

    // Uniform double in [min, max).
    inline double get(double min, double max) {
        std::uniform_real_distribution<double> dist{ min, max };
        return dist(mt);
    }
}
// ───────────────────────────────────────────────────────────────────────────

// "Client" code: no engine, no distribution, no seeding. Just ask.
void simulateCombat() {
    int dmg = Random::get(1, 20);
    std::cout << "you hit for " << dmg << " damage\n";
}

void simulateDrop() {
    double chance = Random::get(0.0, 1.0);
    std::cout << "drop roll = " << chance
              << (chance < 0.1 ? "  RARE!\n" : "\n");
}

int main() {
    for (int i = 0; i < 3; ++i) simulateCombat();
    for (int i = 0; i < 3; ++i) simulateDrop();
}
