// 19.5 — void* basics: store, tag, cast back.
//
// We tag each void* with what's actually behind it, then static_cast back
// before dereferencing. The tag is the load-bearing part — without it the
// cast is a guess and the deref is UB.
//
// Modern C++ replaces this whole pattern with std::variant + std::visit:
// the variant carries the tag for you and the compiler enforces the cast.
#include <iostream>
#include <string>

enum class Tag { Int, Double, CStr };

void print(void* pv, Tag t) {
    switch (t) {
    case Tag::Int:    std::cout << "int    = " << *static_cast<int*>(pv)         << '\n'; break;
    case Tag::Double: std::cout << "double = " << *static_cast<double*>(pv)      << '\n'; break;
    case Tag::CStr:   std::cout << "cstr   = " << static_cast<const char*>(pv)   << '\n'; break;
    }
}

int main() {
    int         i{ 42 };
    double      d{ 3.14 };
    const char* s{ "hello" };

    // T* converts implicitly to void* — the type info is dropped on the floor.
    void* pi{ &i };
    void* pd{ &d };
    void* ps{ const_cast<char*>(s) };   // void* can't be const-qualified the same way;
                                        // the cast-back below restores const-ness

    print(pi, Tag::Int);
    print(pd, Tag::Double);
    print(ps, Tag::CStr);

    // What you CANNOT do with a void*:
    //   *pi;          // error: void has no value
    //   pi + 1;       // error (non-portable): no element size known
    //   delete pi;    // UB: doesn't know what destructor to run

    // Null + void are orthogonal. A void* can be null:
    void* pnull{ nullptr };
    std::cout << "pnull is " << (pnull ? "non-null" : "null") << '\n';
}
