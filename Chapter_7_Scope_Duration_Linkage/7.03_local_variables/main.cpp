// 7.3 — locals: block scope + automatic duration + no linkage.
#include <iostream>
#include <string>

// Tiny RAII trace so we can *see* construction/destruction order.
struct Trace {
    std::string name;
    Trace(std::string n) : name{ std::move(n) } {
        std::cout << "  + " << name << " constructed\n";
    }
    ~Trace() {
        std::cout << "  - " << name << " destroyed\n";
    }
};

void demo() {
    std::cout << "entering demo()\n";
    Trace a{ "a (function-body local)" };

    {
        Trace b{ "b (inner block)" };
        std::cout << "  inside inner block\n";
    }   // b destroyed here

    std::cout << "back in function-body block\n";
}   // a destroyed here

int main() {
    demo();
    std::cout << "demo() returned\n";

    // Locals are *not* zero-initialized by default. Always brace-init.
    int x{};            // value-initialized to 0
    std::cout << "x = " << x << " (value-initialized)\n";
}
