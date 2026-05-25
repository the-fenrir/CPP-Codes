// 27.4 — top-level boundary: specific catch + catch(...) safety net.
#include <iostream>
#include <stdexcept>

// A function that might throw any of several unrelated types. In real code you'd
// avoid throwing ints/strings, but this is exactly what catch(...) is *for*: the
// outermost boundary, where you can't enumerate every possible failure mode.
void mystery(int which) {
    if      (which == 1) throw std::runtime_error{ "std::exception subtype" };
    else if (which == 2) throw 42;                  // not derived from std::exception
    else if (which == 3) throw std::string{ "raw string error" };
    // which == 0 → no throw
}

void run(int which) {
    std::cout << "case " << which << ": ";
    try {
        mystery(which);
        std::cout << "no throw\n";
    } catch (const std::exception& e) {
        std::cout << "std::exception: " << e.what() << '\n';
    } catch (...) {                                  // must be last
        std::cout << "unknown exception (caught by ...)\n";
    }
}

int main() {
    run(0);
    run(1);
    run(2);
    run(3);
    return 0;
}
