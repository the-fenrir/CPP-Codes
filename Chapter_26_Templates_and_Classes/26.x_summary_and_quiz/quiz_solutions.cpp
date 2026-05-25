// Chapter 26 quiz solutions.
//   Q1: Pair1<T>            — single type parameter
//   Q2: Pair<T, U>          — two type parameters
//   Q3: StringValuePair<T>  — inherits from a partial specialization Pair<std::string, T>
#include <iostream>
#include <string>

// ── Q1: Pair1<T> ────────────────────────────────────────────────────
//
// Design notes:
//  • Single type parameter shared by both members. Simplest possible class
//    template — exists to drill the syntax before Q2.
//  • Accessors are `const` and return by `const T&` to avoid copies and to
//    work on `const Pair1<double>` (see p2 in main).
//  • Members are public-by-value-init defaults? Kept private; the data is an
//    invariant-free pair so getters are fine.
template <typename T>
class Pair1 {
    T m_first{};
    T m_second{};
public:
    Pair1(const T& a, const T& b) : m_first{ a }, m_second{ b } {}
    const T& first()  const { return m_first; }
    const T& second() const { return m_second; }
};

// ── Q2: Pair<T, U> ──────────────────────────────────────────────────
//
// Design notes:
//  • Two parameters — the more general version. Q3 will partially specialize
//    *this* template, so it must come first and be the "primary."
//  • Same accessor pattern as Q1.
template <typename T, typename U>
class Pair {
    T m_first{};
    U m_second{};
public:
    Pair(const T& a, const U& b) : m_first{ a }, m_second{ b } {}
    const T& first()  const { return m_first; }
    const U& second() const { return m_second; }
};

// ── Q3a: partial specialization of Pair when T == std::string ───────
//
// Design notes:
//  • Pin the first template argument to std::string; leave U free.
//  • The body of a partial specialization is an entirely independent class,
//    so we repeat the members and the accessors. This is the price of full
//    independence between primary and specialization (cf. 26.4).
template <typename U>
class Pair<std::string, U> {
    std::string m_first{};
    U           m_second{};
public:
    Pair(const std::string& a, const U& b) : m_first{ a }, m_second{ b } {}
    const std::string& first()  const { return m_first; }
    const U&           second() const { return m_second; }
};

// ── Q3b: StringValuePair<T> — inherits from the partial specialization ──
//
// Design notes:
//  • Public inheritance so `first()` / `second()` are inherited as-is.
//  • The constructor forwards through the base — no extra storage here, the
//    whole point is to give the specialization a friendlier name.
//  • `using Pair<std::string, T>::Pair;` would work too; an explicit
//    forwarding ctor reads more clearly in a teaching context.
template <typename T>
class StringValuePair : public Pair<std::string, T> {
public:
    StringValuePair(const std::string& key, const T& value)
        : Pair<std::string, T>{ key, value } {}
};

int main() {
    std::cout << "── Q1: Pair1<T> ──\n";
    Pair1<int> p1{ 5, 8 };
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
    const Pair1<double> p2{ 2.3, 4.5 };
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    std::cout << "\n── Q2: Pair<T, U> ──\n";
    Pair<int, double> q1{ 5, 6.7 };
    std::cout << "Pair: " << q1.first() << ' ' << q1.second() << '\n';
    const Pair<double, int> q2{ 2.3, 4 };
    std::cout << "Pair: " << q2.first() << ' ' << q2.second() << '\n';

    std::cout << "\n── Q3: StringValuePair<T> ──\n";
    StringValuePair<int> svp{ "Hello", 5 };
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
}
