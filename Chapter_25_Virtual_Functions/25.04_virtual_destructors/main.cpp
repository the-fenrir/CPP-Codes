// 25.4 — virtual destructors, and explicit base-call to bypass virtual dispatch.
#include <iostream>

// ── Hierarchy 1: non-virtual ~Base — derived destructor is SKIPPED on delete.
namespace bad {
    class Base {
    public:
        ~Base() { std::cout << "  ~bad::Base\n"; } // not virtual
    };
    class Derived : public Base {
    public:
        ~Derived() { std::cout << "  ~bad::Derived\n"; }
    };
}

// ── Hierarchy 2: virtual ~Base — both destructors run on delete via Base*.
namespace good {
    class Base {
    public:
        virtual ~Base() { std::cout << "  ~good::Base\n"; }
        virtual void greet() const { std::cout << "  good::Base::greet\n"; }
    };
    class Derived : public Base {
    public:
        ~Derived() override { std::cout << "  ~good::Derived\n"; }
        void greet() const override {
            Base::greet();                                 // explicit base call
            std::cout << "  good::Derived::greet (extra)\n";
        }
    };
}

int main() {
    std::cout << "delete via bad::Base* (no virtual dtor — leak!):\n";
    {
        bad::Base* p = new bad::Derived;
        delete p;                       // only ~Base runs — UB territory
    }

    std::cout << "\ndelete via good::Base* (virtual dtor — both run):\n";
    {
        good::Base* p = new good::Derived;
        delete p;                       // ~Derived then ~Base
    }

    std::cout << "\nexplicit base-call inside derived override:\n";
    {
        good::Derived d;
        d.greet();
    }
}
