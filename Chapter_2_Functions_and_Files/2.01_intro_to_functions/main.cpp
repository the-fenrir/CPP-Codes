// 2.1 — basic function definition and call.
#include <iostream>

void printSeparator() {
    std::cout << "----------\n";
}

void greet() {
    printSeparator();              // functions can call other functions
    std::cout << "Hello, world!\n";
    printSeparator();
}

int main() {
    std::cout << "Before greet()\n";
    greet();                       // jump into greet, run it, then resume here
    std::cout << "After greet()\n";
}
