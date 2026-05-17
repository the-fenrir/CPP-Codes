// 7.2 — namespaces partition the global scope.
#include <iostream>

namespace Foo {
    int value{ 1 };
    void print() { std::cout << "Foo::print, value=" << value << '\n'; }
}

namespace Bar {
    int value{ 2 };
    void print() { std::cout << "Bar::print, value=" << value << '\n'; }
}

// Nested namespace (C++17 syntax).
namespace App::Util {
    void greet() { std::cout << "App::Util::greet\n"; }
}

int main() {
    Foo::print();          // qualified call — no ambiguity
    Bar::print();
    App::Util::greet();

    // Namespace alias — local to this scope.
    namespace U = App::Util;
    U::greet();

    // `::name` means "the global scope" explicitly. Here it's the same
    // as unqualified `main`, but it disambiguates when shadowed.
    std::cout << "global Foo::value = " << ::Foo::value << '\n';
}
