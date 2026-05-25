// 25.5 — three flavors of binding, side by side.
#include <iostream>

// ── Free functions for the function-pointer demo (manual dispatch).
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

// ── Classes for early vs. late binding.
class Base {
public:
    virtual int eval(int x) const { return x; }
    virtual ~Base() = default;
};
class Times2 : public Base {
public:
    int eval(int x) const override { return x * 2; }
};
class Plus10 : public Base {
public:
    int eval(int x) const override { return x + 10; }
};

int main() {
    // ── Early binding: static type == dynamic type, compiler knows the target.
    Times2 t;
    std::cout << "early   (Times2::eval): " << t.eval(5) << '\n';  // 10

    // ── Late binding: through a Base*, dispatch picks at runtime.
    Base* p = &t;
    std::cout << "late    (Base* -> Times2): " << p->eval(5) << '\n'; // 10

    Plus10 q;
    p = &q;
    std::cout << "late    (Base* -> Plus10): " << p->eval(5) << '\n'; // 15

    // ── Manual late binding via function pointers — no inheritance involved.
    int (*op)(int, int) = nullptr;
    for (int i = 0; i < 3; ++i) {
        op = (i == 0 ? &add : i == 1 ? &sub : &mul);
        std::cout << "fnptr   op(3,4) = " << op(3, 4) << '\n';
    }
}
