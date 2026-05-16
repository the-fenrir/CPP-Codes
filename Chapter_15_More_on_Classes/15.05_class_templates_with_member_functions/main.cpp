// 15.5 — class template with member functions inside and outside the class body.
#include <iostream>
#include <string>

template <typename A, typename B>
class Pair {
    A m_first;
    B m_second;
public:
    Pair(A a, B b) : m_first{ std::move(a) }, m_second{ std::move(b) } {}

    // Inside the class body — no template header needed here.
    const A& first()  const { return m_first; }

    // Declared here, defined outside.
    const B& second() const;
    void print() const;
};

// Out-of-line member function for a class template: repeat the template header.
template <typename A, typename B>
const B& Pair<A, B>::second() const { return m_second; }

template <typename A, typename B>
void Pair<A, B>::print() const {
    std::cout << '(' << m_first << ", " << m_second << ")\n";
}

int main() {
    Pair<int, double> p1{ 1, 2.5 };
    p1.print();

    // CTAD (C++17): types deduced from arguments.
    Pair p2{ std::string{"name"}, 42 };
    p2.print();

    std::cout << "p1.first=" << p1.first() << " p1.second=" << p1.second() << '\n';
}
