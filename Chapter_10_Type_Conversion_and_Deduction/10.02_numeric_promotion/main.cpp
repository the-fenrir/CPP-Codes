// 10.2 — numeric promotion: value-preserving widening to int / double.
#include <iostream>
#include <typeinfo>

template <typename T>
void show(const char* expr, const T& value) {
    std::cout << expr << " -> type " << typeid(T).name()
              << ", value " << value << '\n';
}

int main() {
    // Integral promotion: anything narrower than int -> int.
    char    c  = 'A';
    short   s  = 100;
    bool    b  = true;

    // Each of these expressions promotes to int before evaluation.
    show("c + 0",  c + 0);
    show("s + 0",  s + 0);
    show("b + 0",  b + 0);
    show("s + s",  s + s);   // even short + short -> int

    // Floating-point promotion: float -> double.
    float f = 3.5f;
    show("f + 0.0", f + 0.0);  // 0.0 is double, drags f up to double too

    // Direct cout printing of small types is NOT promotion — operator<< has its own overloads.
    std::cout << "raw c prints as: " << c << '\n';
    std::cout << "c + 0 prints as: " << (c + 0) << "  (promoted to int)\n";
}
