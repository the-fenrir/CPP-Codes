// 7.5 — name hiding: inner declarations hide same-named outer ones.
#include <iostream>

int value{ 100 };           // global

void shadow_global() {
    int value{ 7 };         // shadows ::value within this function
    std::cout << "  local value  = " << value   << '\n';
    std::cout << "  global value = " << ::value << '\n'; // reach via ::
}

void shadow_local() {
    int x{ 1 };
    std::cout << "  outer x = " << x << '\n';
    {
        int x{ 2 };         // shadows the outer x — and there's NO syntax
                            // to reach the outer x from in here.
        std::cout << "  inner x = " << x << '\n';
    }
    std::cout << "  outer x after block = " << x << "  (untouched)\n";
}

int main() {
    std::cout << "── shadow_global ──\n";  shadow_global();
    std::cout << "── shadow_local  ──\n";  shadow_local();

    std::cout << "global value at end = " << value << '\n';
}
