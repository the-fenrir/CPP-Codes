// 12.10 — pass-by-address: caller may pass nullptr; callee must check.
#include <iostream>

void incrementOrIgnore(int* p) {
    if (!p) {
        std::cout << "incrementOrIgnore: null — nothing to do\n";
        return;
    }
    ++(*p);
}

void print(const int* p) {       // const T* — read-only, may be null
    if (!p) { std::cout << "print: null\n"; return; }
    std::cout << "print: " << *p << '\n';
}

int main() {
    int x { 5 };
    incrementOrIgnore(&x);
    std::cout << "after increment(&x): x = " << x << '\n';

    incrementOrIgnore(nullptr);  // legitimate "no object" argument

    print(&x);
    print(nullptr);

    // Pass-by-reference equivalent (next page) — no null possible:
    auto incrementRef = [](int& n) { ++n; };
    incrementRef(x);
    std::cout << "after incrementRef(x): x = " << x << '\n';
}
