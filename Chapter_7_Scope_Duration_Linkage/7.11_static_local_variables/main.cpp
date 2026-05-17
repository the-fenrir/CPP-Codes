// 7.11 — static local: local scope, static duration, value persists.
#include <iostream>

int next_id() {
    static int s_id{ 0 };     // initialized once, on first call
    return ++s_id;
}

void greet(const char* name) {
    static bool s_first_time{ true };
    if (s_first_time) {
        std::cout << "(first-time greeting)\n";
        s_first_time = false;
    }
    std::cout << "  hello, " << name << '\n';
}

int main() {
    std::cout << "next_id() = " << next_id() << '\n';   // 1
    std::cout << "next_id() = " << next_id() << '\n';   // 2
    std::cout << "next_id() = " << next_id() << '\n';   // 3

    greet("Alice");
    greet("Bob");
    greet("Carol");
}
