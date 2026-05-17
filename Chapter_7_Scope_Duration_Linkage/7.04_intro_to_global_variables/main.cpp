// 7.4 — globals: file scope + static duration + (default) external linkage.
#include <iostream>

// Non-const global. Zero-initialized at program start.
int g_counter;                  // == 0

// const global. Internal linkage by default (see 7.6).
constexpr int g_max{ 100 };

void bump() {
    ++g_counter;                // visible because declared above
    std::cout << "  bump(): g_counter = " << g_counter << '\n';
}

int main() {
    std::cout << "start: g_counter = " << g_counter
              << ", g_max = " << g_max << '\n';

    bump();
    bump();
    bump();

    std::cout << "end:   g_counter = " << g_counter << '\n';
    // Note: g_max cannot be reassigned (it's constexpr).
}
