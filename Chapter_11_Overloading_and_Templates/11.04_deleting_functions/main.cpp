// 11.4 — = delete forbids specific overloads from being called.
#include <iostream>

void printInt(int x) {
    std::cout << "printInt(int) = " << x << '\n';
}

// Without this delete, printInt('a') would promote 'a' to int and print 97 silently.
// With it, the call is a hard error — caller has to be explicit.
void printInt(char) = delete;

// Same trick to forbid bool (which converts to int):
void printInt(bool) = delete;

int main() {
    printInt(42);                       // fine
    printInt(static_cast<int>('a'));    // explicit conversion — caller chose this
    // printInt('a');                   // error: call to deleted function 'printInt(char)'
    // printInt(true);                  // error: call to deleted function 'printInt(bool)'
}
