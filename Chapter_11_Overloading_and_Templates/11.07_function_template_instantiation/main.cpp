// 11.7 — per-type instantiation: separate functions, separate statics.
#include <iostream>

template <typename T>
int count(T) {
    static int c{ 0 };
    return ++c;
}

// Non-template + template overload. Non-template wins on an exact match.
int foo(int n) { return n + 10; }

template <typename T>
int foo(T n) { return n; }

int main() {
    std::cout << "── per-type static counters ──\n";
    std::cout << count(1)         << '\n';   // count<int>: 1
    std::cout << count(2)         << '\n';   // count<int>: 2  (same instantiation)
    std::cout << count(3.14)      << '\n';   // count<double>: 1 (different instantiation)
    std::cout << count<double>(7) << '\n';   // count<double>: 2 (7 converts to double)

    std::cout << "\n── template vs. non-template ──\n";
    std::cout << foo(1)        << '\n';      // non-template foo(int) — exact match wins ⇒ 11
    short s{ 2 };
    std::cout << foo(s)        << '\n';      // template foo<short> — no conversion needed ⇒ 2
    std::cout << foo<int>(4)   << '\n';      // forced template foo<int> ⇒ 4
    std::cout << foo<int>(s)   << '\n';      // forced template foo<int>, s promotes ⇒ 2
    std::cout << foo<>(6)      << '\n';      // empty <> forces template, deduces int ⇒ 6
}
