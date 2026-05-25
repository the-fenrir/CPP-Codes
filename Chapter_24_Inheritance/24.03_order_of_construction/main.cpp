// 24.3 — Construction goes base→derived; destruction goes derived→base.
//   Three-level hierarchy A ← B ← C makes it obvious.
#include <iostream>

class A {
public:
    A()  { std::cout << "A()\n"; }
    ~A() { std::cout << "~A()\n"; }
};

class B : public A {
public:
    B()  { std::cout << "B()\n"; }
    ~B() { std::cout << "~B()\n"; }
};

class C : public B {
public:
    C()  { std::cout << "C()\n"; }
    ~C() { std::cout << "~C()\n"; }
};

int main() {
    std::cout << "-- create C c; --\n";
    {
        C c;          // A() B() C() … then ~C() ~B() ~A() at }
        std::cout << "-- (object alive) --\n";
    }

    std::cout << "-- multiple objects in one scope --\n";
    {
        A a;          // constructed first
        C c;          // constructed second
        std::cout << "-- (both alive; destroyed in reverse order) --\n";
    }                 // ~C ~B ~A, then ~A
}
