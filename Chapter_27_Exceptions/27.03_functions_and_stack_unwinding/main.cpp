// 27.3 — stack unwinding visibly destroys locals as the exception bubbles up.
#include <iostream>
#include <stdexcept>
#include <string>

// Trace logs construction and destruction. Watch the destructor order in the
// output — that's stack unwinding running real cleanup at every level.
struct Trace {
    std::string label;
    explicit Trace(std::string s) : label{ std::move(s) } {
        std::cout << "  + " << label << '\n';
    }
    ~Trace() {
        std::cout << "  - " << label << '\n';
    }
};

void deepest() {
    Trace t{ "deepest() local" };
    throw std::runtime_error{ "kaboom from deepest()" };
    // unreachable
}

void middle() {
    Trace t{ "middle() local" };
    deepest();
    // unreachable: the throw propagates through here, but t's destructor still runs
}

void outer() {
    Trace t{ "outer() local" };
    middle();
}

int main() {
    std::cout << "calling outer()...\n";
    try {
        outer();
    } catch (const std::exception& e) {
        std::cout << "caught in main: " << e.what() << '\n';
    }
    std::cout << "main continues normally\n";
    return 0;
}
