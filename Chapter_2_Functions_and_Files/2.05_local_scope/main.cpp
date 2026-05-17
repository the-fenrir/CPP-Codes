// 2.5 — locals are private to their function and don't persist across calls.
#include <iostream>

void counter() {
    int count{ 0 };                  // fresh every call
    ++count;
    std::cout << "counter local count = " << count << '\n';
}

void reporter() {
    int count{ 100 };                // a completely different `count`
    std::cout << "reporter local count = " << count << '\n';
}

int main() {
    counter();                       // prints 1
    counter();                       // prints 1 again — no persistence
    reporter();                      // prints 100
    // std::cout << count;           // would not compile: not in scope here
}
