// 11.9 — non-type template parameters: values, not types.
#include <iostream>

// Classic compile-time factorial via NTTP recursion.
template <int N>
constexpr int factorial() {
    return N * factorial<N - 1>();
}
template <>
constexpr int factorial<0>() {
    return 1;
}

// NTTP used as a literal count inside the body. C++20 `auto` NTTP — N's
// type is deduced from the call site.
template <auto N>
void print_n_times(const char* s) {
    for (auto i = decltype(N){ 0 }; i < N; ++i)
        std::cout << s;
    std::cout << '\n';
}

int main() {
    static_assert(factorial<5>() == 120);    // proves it ran at compile time

    std::cout << "5! = " << factorial<5>()  << '\n';
    std::cout << "8! = " << factorial<8>()  << '\n';

    print_n_times<3>("hi ");                 // N is int by default
    print_n_times<5>("-");                   // separate instantiation
}
