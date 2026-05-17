// 8.13 — intro to <random>: engine + distribution, seeded vs. fixed.
#include <iostream>
#include <random>

int main() {
    // ── Non-deterministic seed ──
    //   random_device produces a hardware-/OS-flavored seed when available.
    //   We use it once to seed the engine, then forget about it.
    std::mt19937 engine{ std::random_device{}() };
    std::uniform_int_distribution<int> d6{ 1, 6 };

    std::cout << "five d6 rolls (seeded): ";
    for (int i = 0; i < 5; ++i) std::cout << d6(engine) << ' ';
    std::cout << '\n';

    // ── Reproducible run with a fixed seed ──
    //   Same seed → same sequence, every time. Useful for debugging and tests.
    std::mt19937 fixedEngine{ 42 };
    std::cout << "five d6 rolls (seed=42): ";
    for (int i = 0; i < 5; ++i) std::cout << d6(fixedEngine) << ' ';
    std::cout << "  (deterministic — re-run to confirm)\n";
}
