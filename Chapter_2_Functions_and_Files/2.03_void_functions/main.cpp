// 2.3 — void functions: side effects only, no return value.
#include <iostream>

void printGreeting() {
    std::cout << "Hello!\n";
    // no return needed
}

void printAbs(int x) {
    if (x < 0) {
        std::cout << -x << '\n';
        return;                      // early exit is allowed in void
    }
    std::cout << x << '\n';
}

int main() {
    printGreeting();
    printAbs(-7);
    printAbs(3);

    // int x{ printGreeting() };     // would not compile: void in value context
}
