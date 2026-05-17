// 11.5 — default arguments cover several call shapes with one function.
#include <iostream>

void greet(const char* name = "world", int times = 1) {
    for (int i = 0; i < times; ++i)
        std::cout << "Hello, " << name << "!\n";
}

// ── Ambiguity trap (commented so the file still compiles) ─────
// void print();                        // (A)
// void print(int x = 0);               // (B)
// int main() { print(); }              // error: ambiguous — (A) and (B) both match.

int main() {
    greet();                    // Hello, world!
    greet("Alice");             // Hello, Alice!
    greet("Bob", 3);            // Hello, Bob! x3
}
