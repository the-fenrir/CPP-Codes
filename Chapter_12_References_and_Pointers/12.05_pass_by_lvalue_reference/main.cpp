// 12.5 — pass-by-reference: the function can mutate the caller's object.
#include <iostream>
#include <string>

void increment(int& n) {        // n is an alias for the caller's variable
    ++n;
}

void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

// Compare: pass-by-value copies; modifications stay local.
void incrementByValue(int n) {
    ++n;                        // mutates the local copy only
    (void)n;
}

int main() {
    int x { 5 };
    incrementByValue(x);
    std::cout << "after incrementByValue(x): x = " << x << "  (unchanged)\n";

    increment(x);
    std::cout << "after increment(x):        x = " << x << "  (mutated)\n";

    int a { 1 }, b { 2 };
    swap(a, b);
    std::cout << "after swap(a,b): a = " << a << ", b = " << b << '\n';

    // These would fail to compile — argument must be a modifiable lvalue:
    // increment(5);            // literal: rvalue
    // increment(x + 1);        // arithmetic: rvalue
    // const int c{ 7 };
    // increment(c);            // const: not modifiable

    // For large objects, pass-by-reference avoids the copy — but if you
    // don't need to mutate, prefer const T& (next lesson):
    std::string greeting { "hello" };
    auto byRef = [](std::string& s) { s += ", world"; };
    byRef(greeting);
    std::cout << "greeting = " << greeting << '\n';
}
