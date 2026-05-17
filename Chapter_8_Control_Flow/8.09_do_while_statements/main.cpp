// 8.9 — do-while: always runs at least once. Input-validation pattern.
//        We simulate "user input" with a small array so the build is reproducible.
#include <array>
#include <iostream>

int main() {
    // Simulated user inputs — first three are invalid, last one is valid.
    constexpr std::array<int, 4> fakeInput{ -1, 0, 7, 3 };
    std::size_t cursor{ 0 };

    // ── Classic input-validation pattern ──
    //   - Always prompt at least once (do-while).
    //   - choice must be in scope at `while(cond)`, so declare it before the loop.
    int choice{};
    do {
        std::cout << "Pick a menu option (1-5): ";
        choice = fakeInput[cursor++];
        std::cout << choice << '\n';
        if (choice < 1 || choice > 5)
            std::cout << "  invalid, try again.\n";
    } while (choice < 1 || choice > 5);

    std::cout << "You chose " << choice << ".\n";
}
