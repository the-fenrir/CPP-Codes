// 14.4 — const objects can only call const member functions.
#include <iostream>

class Counter {
    int m_count{ 0 };
public:
    void increment()      { ++m_count; }          // non-const: mutates
    int  value()    const { return m_count; }     // const: read-only

    // Overload on const-ness — different versions for const vs. non-const objects.
    void describe()       { std::cout << "non-const: count=" << m_count << '\n'; }
    void describe() const { std::cout << "const:     count=" << m_count << '\n'; }
};

int main() {
    Counter c;
    c.increment();
    c.describe();         // calls the non-const overload

    const Counter cc{ };
    std::cout << "const value() = " << cc.value() << '\n';
    cc.describe();        // calls the const overload
    // cc.increment();    // ← uncomment: ERROR. can't call non-const fn on const object.
}
