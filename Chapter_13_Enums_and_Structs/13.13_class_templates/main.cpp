// 13.13 — A first class template.
#include <iostream>
#include <string>

// One parameter — both members share a type.
template <typename T>
struct Pair {
    T first;
    T second;
};

// Two parameters — independent types per member.
template <typename T, typename U>
struct Pair2 {
    T first;
    U second;
};

template <typename T>
void print(const Pair<T>& p) {
    std::cout << '[' << p.first << ", " << p.second << "]\n";
}

template <typename T, typename U>
void print(const Pair2<T, U>& p) {
    std::cout << '[' << p.first << ", " << p.second << "]\n";
}

int main() {
    Pair<int>          a{ 1, 2 };
    Pair<double>       b{ 1.5, 2.5 };
    Pair2<int, double> c{ 7, 9.5 };
    Pair2<std::string, int> d{ "score", 100 };

    print(a);
    print(b);
    print(c);
    print(d);
}
