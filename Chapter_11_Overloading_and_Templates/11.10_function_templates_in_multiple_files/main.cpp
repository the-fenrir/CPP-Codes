// 11.10 — caller only #includes the template header.
#include "max.h"
#include <iostream>

int main() {
    std::cout << my_max(3, 7)       << '\n';   // instantiates my_max<int>
    std::cout << my_max(2.5, 1.25)  << '\n';   // instantiates my_max<double>
}
