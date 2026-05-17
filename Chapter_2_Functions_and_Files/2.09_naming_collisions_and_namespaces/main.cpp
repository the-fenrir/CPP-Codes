// 2.9 — same function name, different namespaces, no collision.
#include <iostream>
#include <string>

namespace math {
    int add(int a, int b) { return a + b; }
}

namespace string_ops {
    std::string add(const std::string& a, const std::string& b) { return a + b; }
}

int main() {
    std::cout << "math::add(2, 3)            = " << math::add(2, 3) << '\n';
    std::cout << "string_ops::add(\"a\", \"b\")  = " << string_ops::add("a", "b") << '\n';
    // add(2, 3);                  // would not compile: which `add`?
}
