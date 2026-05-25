// 24.7 — Derived can override, and can call back to the base via Base::fn().
#include <iostream>

class Base {
public:
    void identify() const {
        std::cout << "I am a Base.\n";
    }
};

class Derived : public Base {
public:
    // Same name → hides Base::identify() on a Derived object.
    // Qualify with Base:: to reuse the parent's logic; a bare identify()
    // here would recurse into itself.
    void identify() const {
        Base::identify();
        std::cout << "I am also a Derived.\n";
    }
};

int main() {
    Base b;
    b.identify();   // I am a Base.

    Derived d;
    d.identify();   // Base line, then Derived line.

    // Non-virtual: through a Base reference, only Base::identify() runs.
    Base& bref = d;
    bref.identify(); // I am a Base.
}
