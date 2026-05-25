// 24.8 — Hide or delete inherited functions in the derived class.
#include <iostream>

class Base {
public:
    void do_a() const { std::cout << "Base::do_a\n"; }
    void do_b() const { std::cout << "Base::do_b\n"; }
};

class Derived : public Base {
private:
    // Demote do_a to private — outside callers can no longer use it through Derived.
    using Base::do_a;

public:
    // Delete do_b entirely as far as derived users are concerned.
    void do_b() const = delete;

    void run() const {
        do_a();        // OK inside the class — visibility change only affects callers.
        Base::do_b();  // Still reachable via base qualification.
    }
};

int main() {
    Derived d;
    d.run();

    // d.do_a();   // ERROR: now private in Derived
    // d.do_b();   // ERROR: deleted in Derived

    // Casting away the derived view bypasses the hiding — the base members are
    // still physically there.
    static_cast<const Base&>(d).do_a();
    static_cast<const Base&>(d).do_b();
}
