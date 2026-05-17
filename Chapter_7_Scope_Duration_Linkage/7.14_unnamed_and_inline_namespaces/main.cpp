// 7.14 — unnamed (internal linkage) and inline (transparent) namespaces.
#include <iostream>

// ── Unnamed namespace: everything inside has internal linkage. ──
namespace {
    int helper_value{ 7 };
    void helper() {
        std::cout << "  helper(): helper_value = " << helper_value << '\n';
    }
}

// ── Inline namespace: V2's names are reachable from MyLib directly. ──
namespace MyLib {
    inline namespace V2 {
        void api() { std::cout << "  MyLib::V2::api (default)\n"; }
    }

    namespace V1 {
        void api() { std::cout << "  MyLib::V1::api (legacy)\n"; }
    }
}

int main() {
    helper();                   // resolves to the unnamed-namespace one

    MyLib::api();               // calls V2::api thanks to `inline`
    MyLib::V2::api();           // explicit version
    MyLib::V1::api();           // legacy still reachable
}
