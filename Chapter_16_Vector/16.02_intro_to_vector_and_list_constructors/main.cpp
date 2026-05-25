// 16.2 — vector constructors: list vs. length vs. fill, plus CTAD.
#include <iostream>
#include <vector>

template <typename T>
void print(std::string_view label, const std::vector<T>& v) {
    std::cout << label << " (size=" << v.size() << "): ";
    for (std::size_t i{ 0 }; i < v.size(); ++i)
        std::cout << v[i] << (i + 1 == v.size() ? '\n' : ' ');
}

int main() {
    // List constructor: braces => fill with these values.
    std::vector<int> a{ 1, 2, 3 };
    print("list  {1,2,3}", a);

    // Length constructor: parens => N default-initialized elements (0 for int).
    std::vector<int> b(5);
    print("length (5)   ", b);

    // Length-and-fill: N copies of a value.
    std::vector<int> c(4, 7);
    print("fill   (4,7) ", c);

    // CTAD (C++17): <int> deduced from initializer list.
    std::vector d{ 10, 20, 30 };
    print("CTAD  {10..} ", d);

    // const vector — values cannot be reassigned.
    const std::vector e{ 1, 2, 3 };
    // e[0] = 9;  // error: assignment of read-only location
    print("const        ", e);
}
