// 22.4 — std::move is just a cast.
//
// Demonstrates: (a) moving a string into a vector avoids a copy,
//               (b) after move the source is "valid but unspecified",
//               (c) a generic swap built on std::move.
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename T>
void mySwap(T& a, T& b) {
    T tmp{ std::move(a) };
    a = std::move(b);
    b = std::move(tmp);
}

int main() {
    std::string s{ "longish string so SSO doesn't hide the buffer" };

    std::vector<std::string> v;
    v.push_back(std::move(s));      // moves s into the vector

    std::cout << "v[0] = \"" << v[0] << "\"\n";
    std::cout << "s    = \"" << s    << "\"  (valid but unspecified — usually empty)\n";

    std::string x{ "hello" }, y{ "world" };
    mySwap(x, y);
    std::cout << "after mySwap: x = " << x << ", y = " << y << '\n';
}
