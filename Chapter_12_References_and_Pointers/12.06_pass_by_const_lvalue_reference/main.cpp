// 12.6 — const T& is the default for non-trivial inputs.
#include <iostream>
#include <string>

void printByValue(std::string s) {       // copies the string on every call
    std::cout << s << '\n';
}

void printByConstRef(const std::string& s) { // no copy
    std::cout << s << '\n';
}

// Tiny types: pass by value. const int& would be slower in practice.
int square(int n) { return n * n; }

int main() {
    std::string greeting { "hello, world" };

    printByValue(greeting);              // copy
    printByConstRef(greeting);           // no copy

    // const T& accepts literals/temporaries (materialized into a temp string):
    printByConstRef("from a string literal");

    // It also accepts const objects:
    const std::string forever { "const lvalue" };
    printByConstRef(forever);

    // Tiny built-in: pass by value.
    std::cout << "square(7) = " << square(7) << '\n';
}
