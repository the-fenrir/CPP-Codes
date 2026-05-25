// 21.11 — `explicit operator T()`: opt-in conversion *from* your type *to* T.
#include <iostream>

class Cents {
    int m_cents{};
public:
    explicit Cents(int c) : m_cents{ c } {}
    explicit operator int() const { return m_cents; }   // explicit — opt-in only
};

class Handle {
    int m_fd{ -1 };  // -1 == invalid
public:
    explicit Handle(int fd) : m_fd{ fd } {}
    explicit operator bool() const { return m_fd >= 0; }
};

int main() {
    Cents c{ 42 };
    int n = static_cast<int>(c);             // OK — explicit cast
    // int bad = c;                          // would NOT compile — explicit blocks implicit
    std::cout << "c as int: " << n << '\n';

    Handle good{ 3 };
    Handle bad{ -1 };
    // `if (h)` is a contextual conversion to bool — `explicit operator bool` allows it
    // without allowing `int x = h + 1;` style mistakes.
    std::cout << "good open? " << std::boolalpha << static_cast<bool>(good) << '\n';
    if (good) std::cout << "good is usable\n";
    if (!bad) std::cout << "bad is not usable\n";
}
