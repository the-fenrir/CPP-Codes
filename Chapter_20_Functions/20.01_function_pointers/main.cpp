// 20.1 — function pointers: raw pointers, type aliases, and std::function.
#include <functional>
#include <iostream>

bool ascending (int a, int b) { return a < b; }
bool descending(int a, int b) { return a > b; }

// Takes a comparator and prints the "best" of three numbers under it.
// The parameter type `bool (*cmp)(int,int)` declares a pointer to a function
// taking two ints and returning bool.
void selectAndPrint(int a, int b, int c, bool (*cmp)(int, int)) {
    int best = a;
    if (cmp(b, best)) best = b;
    if (cmp(c, best)) best = c;
    std::cout << "best = " << best << '\n';
}

// Same idea via std::function — accepts function pointers AND lambdas
// (even capturing ones). The cost: type erasure, indirect call.
void selectAndPrintFn(int a, int b, int c, std::function<bool(int,int)> cmp) {
    int best = a;
    if (cmp(b, best)) best = b;
    if (cmp(c, best)) best = c;
    std::cout << "best (fn) = " << best << '\n';
}

int main() {
    using Cmp = bool(*)(int, int);              // type alias keeps signatures readable

    Cmp c1 = ascending;                          // function name decays to address
    Cmp c2 = &descending;                        // explicit & — same thing
    std::cout << "c1(3,5) = " << c1(3, 5) << '\n';
    std::cout << "(*c2)(3,5) = " << (*c2)(3, 5) << '\n';

    selectAndPrint(7, 2, 9, ascending);          // pass behavior as data
    selectAndPrint(7, 2, 9, descending);

    int threshold = 5;
    // Capturing lambda — cannot bind to a raw function pointer, but std::function handles it.
    selectAndPrintFn(7, 2, 9,
        [threshold](int a, int b) { return (a > threshold) && (a < b); });
}
