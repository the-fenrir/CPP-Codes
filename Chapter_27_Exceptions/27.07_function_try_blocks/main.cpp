// 27.7 — function-try-block on a constructor catches a throw from the member
// initializer list. The exception is implicitly rethrown — the object cannot
// be "rescued" because it never finished constructing.
#include <iostream>
#include <stdexcept>

// Member type that throws during construction.
struct Risky {
    Risky(int v) {
        if (v < 0) throw std::runtime_error{ "Risky: negative value" };
        std::cout << "  Risky(" << v << ") constructed\n";
    }
    ~Risky() { std::cout << "  ~Risky\n"; }
};

// Owner has a Risky member. If Risky's constructor throws, the body of a
// regular try {} inside the ctor body would never run — the init list aborts
// before we get there. A function-try-block catches it.
class Owner {
    Risky m_r;
public:
    Owner(int v)
    try : m_r{ v } {
        std::cout << "  Owner body ran\n";
    } catch (const std::exception& e) {
        std::cout << "  [function-try-block] caught: " << e.what()
                  << " — implicit rethrow follows\n";
        // No explicit rethrow needed; constructor function-try-blocks
        // rethrow automatically at the end of the catch. We CANNOT
        // suppress the exception — the object never finished constructing.
    }
};

int main() {
    std::cout << "(1) successful construction:\n";
    try {
        Owner ok{ 5 };
    } catch (const std::exception& e) {
        std::cout << "  unexpected: " << e.what() << '\n';
    }

    std::cout << "\n(2) failing construction:\n";
    try {
        Owner bad{ -1 };
        std::cout << "  unreachable\n";
    } catch (const std::exception& e) {
        std::cout << "  main caught: " << e.what() << '\n';
    }
    return 0;
}
