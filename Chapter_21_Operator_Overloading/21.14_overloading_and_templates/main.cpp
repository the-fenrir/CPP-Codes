// 21.14 — same template, three types: each must supply the operators the template uses.
#include <iostream>
#include <string>

template <typename T>
const T& pick_max(const T& a, const T& b) {
    return (a < b) ? b : a;   // ← demands T have operator<
}

class Cents {
    int m_cents{};
public:
    explicit Cents(int c) : m_cents{ c } {}
    int value() const { return m_cents; }
    // Provide what the template needs:
    friend bool operator<(const Cents& a, const Cents& b) { return a.m_cents < b.m_cents; }
    friend std::ostream& operator<<(std::ostream& o, const Cents& c) { return o << c.m_cents << "c"; }
};

int main() {
    std::cout << "pick_max(3, 7)              = " << pick_max(3, 7) << '\n';
    std::cout << "pick_max(\"apple\", \"pear\")    = " << pick_max(std::string{"apple"}, std::string{"pear"}) << '\n';
    std::cout << "pick_max(Cents{5}, Cents{8}) = " << pick_max(Cents{5}, Cents{8}) << '\n';
}
