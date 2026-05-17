// 13.14 — CTAD on a class template, with an explicit deduction guide.
// Under C++20, aggregate CTAD works without the guide; under C++17 the
// guide is required for aggregates. We include the guide for clarity.
#include <iostream>

template <typename T>
struct Pair {
    T first;
    T second;
};

// Deduction guide: "constructing Pair with (T, T) means Pair<T>."
template <typename T>
Pair(T, T) -> Pair<T>;

template <typename T>
void print(const Pair<T>& p) {
    std::cout << '[' << p.first << ", " << p.second << "]\n";
}

int main() {
    Pair p1{ 1, 2 };           // CTAD: Pair<int>
    Pair p2{ 1.5, 2.5 };       // CTAD: Pair<double>
    Pair<int> p3{ 7, 8 };      // explicit, still works

    print(p1);
    print(p2);
    print(p3);

    // Pair bad{ 1, 2.5 };     // would fail to deduce T uniquely (int vs double)
}
