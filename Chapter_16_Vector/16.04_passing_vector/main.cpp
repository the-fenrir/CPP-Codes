// 16.4 — passing std::vector: by const ref (default), by ref (mutating),
// and as a template for any element type.
#include <iostream>
#include <vector>

// Read-only access. No copy.
void printInts(const std::vector<int>& v) {
    std::cout << "size=" << v.size() << ":";
    for (int x : v) std::cout << ' ' << x;
    std::cout << '\n';
}

// Mutating access. Caller's vector changes.
void doubleAll(std::vector<int>& v) {
    for (auto& x : v) x *= 2;
}

// Template — works for any element type that supports the operations we use.
template <typename T>
void printAny(const std::vector<T>& v) {
    std::cout << "[generic size=" << v.size() << "]:";
    for (const auto& x : v) std::cout << ' ' << x;
    std::cout << '\n';
}

int main() {
    std::vector v{ 1, 2, 3, 4 };
    printInts(v);

    doubleAll(v);
    printInts(v);

    std::vector<double> d{ 1.5, 2.5, 3.5 };
    printAny(d);
    printAny(v);  // also fine — template instantiates for int too
}
