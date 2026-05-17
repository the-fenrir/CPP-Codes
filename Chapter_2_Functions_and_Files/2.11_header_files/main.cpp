// 2.11 — caller pulls in the declarations via the header.
#include "add.h"
#include <iostream>

int main() {
    std::cout << "add(7, 3)      = " << add(7, 3) << '\n';
    std::cout << "subtract(7, 3) = " << subtract(7, 3) << '\n';
}
