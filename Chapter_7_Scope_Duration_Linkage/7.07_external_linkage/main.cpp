// 7.7 — caller sees only the header; the linker resolves the names
// to the definitions in globals.cpp.
#include "globals.h"
#include <iostream>

int main() {
    std::cout << "start: g_counter = " << g_counter
              << ", g_max = " << g_max << '\n';

    for (int i = 0; i < 3; ++i)
        ++g_counter;

    std::cout << "end:   g_counter = " << g_counter << '\n';
}
