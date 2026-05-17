// 11.1 — three overloads of the same name, picked by argument types.
#include <iostream>
#include <string>

int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

// Same conceptual operation (combine two things) — overload is justified.
std::string add(const std::string& a, const std::string& b) {
    return a + b;
}

int main() {
    std::cout << add(2, 3) << '\n';                             // int overload
    std::cout << add(1.5, 2.25) << '\n';                        // double overload
    std::cout << add(std::string{ "foo" }, std::string{ "bar" }) << '\n';  // string overload
}
