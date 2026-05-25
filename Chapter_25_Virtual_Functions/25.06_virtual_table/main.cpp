// 25.6 — vtable visible only via sizeof; behavior visible via virtual dispatch.
#include <iostream>

struct PlainPair { int a; int b; };          // no virtuals → no vptr

class PolyPair {
public:
    int a;
    int b;
    PolyPair(int x, int y) : a{ x }, b{ y } {}
    virtual int sum() const { return a + b; } // a virtual ⇒ class has a vtable
    virtual ~PolyPair() = default;
};

class WeightedPair : public PolyPair {
public:
    int weight;
    WeightedPair(int x, int y, int w) : PolyPair{ x, y }, weight{ w } {}
    int sum() const override { return (a + b) * weight; }
};

int main() {
    std::cout << "sizeof(PlainPair) = " << sizeof(PlainPair) << '\n';
    std::cout << "sizeof(PolyPair)  = " << sizeof(PolyPair)
              << "  (PlainPair + vptr)\n";

    PolyPair        p{ 3, 4 };
    WeightedPair    w{ 3, 4, 10 };

    // Through PolyPair*, the vtable selects the right sum() at runtime.
    PolyPair* zoo[] = { &p, &w };
    for (auto* x : zoo)
        std::cout << "x->sum() = " << x->sum() << '\n'; // 7, then 70
}
