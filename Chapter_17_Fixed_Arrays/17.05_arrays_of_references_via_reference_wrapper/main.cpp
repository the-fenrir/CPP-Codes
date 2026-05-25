// 17.5 — std::array<std::reference_wrapper<T>, N> to store "references."
#include <array>
#include <functional>   // std::reference_wrapper, std::ref
#include <iostream>

int main() {
    int a { 10 };
    int b { 20 };
    int c { 30 };

    // std::array<int&, 3>            // ILLEGAL — references aren't objects
    // std::array<std::reference_wrapper<int>, 3> refs { a, b, c }; // also works

    std::array refs { std::ref(a), std::ref(b), std::ref(c) };  // CTAD

    std::cout << "before: " << a << ' ' << b << ' ' << c << '\n';

    // Mutate the originals through the wrappers.
    refs[0].get() = 100;       // explicit .get() — clear intent
    refs[1].get() += 5;

    std::cout << "after:  " << a << ' ' << b << ' ' << c << '\n';

    // The wrapper converts implicitly to int& in most contexts.
    int sum { 0 };
    for (int x : refs) sum += x;   // implicit conversion fires here
    std::cout << "sum = " << sum << '\n';
}
