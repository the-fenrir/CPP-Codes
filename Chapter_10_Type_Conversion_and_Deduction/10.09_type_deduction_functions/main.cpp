// 10.9 — auto return types and trailing return types.
#include <iostream>
#include <typeinfo>

// 1) auto return: compiler deduces from the return statement.
auto square(int x) {
    return x * x;          // -> int
}

// 2) Trailing return type: explicit, equivalent to `int sub(int, int)`.
auto sub(int a, int b) -> int {
    return a - b;
}

// 3) Trailing return shines when the type depends on the operands.
template <typename A, typename B>
auto add(A a, B b) -> decltype(a + b) {
    return a + b;
}

// 4) All return paths must deduce to the same type — uncomment to see the error.
// auto inconsistent(bool flag) {
//     if (flag) return 1;     // int
//     else      return 1.5;   // double  -> ill-formed: differing deduced types
// }

int main() {
    auto s = square(7);
    std::cout << "square(7)   = " << s   << " (type " << typeid(s).name() << ")\n";
    std::cout << "sub(10, 3)  = " << sub(10, 3) << '\n';

    auto m = add(2, 3.5);  // int + double -> double, by usual arithmetic conversions
    std::cout << "add(2,3.5)  = " << m << " (type " << typeid(m).name() << ")\n";
}
