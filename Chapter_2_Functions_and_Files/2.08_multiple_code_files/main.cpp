// 2.8 — caller: only needs the declaration, which it gets from the header.
#include "add.h"
#include <iostream>

int main() {
    std::cout << "add(3, 4) = " << add(3, 4) << '\n';
    std::cout << "add(10, -7) = " << add(10, -7) << '\n';
}
