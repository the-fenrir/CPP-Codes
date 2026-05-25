// 20.6 — lambdas: declare, pass to algorithms, write generic, decay to fn-ptr.
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

int main() {
    // ── 1. Store with `auto`. Each lambda has a unique unnamed type. ──
    auto square = [](int x) { return x * x; };
    std::cout << "square(7) = " << square(7) << '\n';

    // ── 2. Inline predicate for an STL algorithm. ──
    std::vector<int> v{ 5, 2, 8, 1, 9, 3 };
    std::sort(v.begin(), v.end(),
              [](int a, int b) { return a > b; });     // descending
    std::cout << "sorted desc:";
    for (int x : v) std::cout << ' ' << x;
    std::cout << '\n';

    auto bigCount = std::count_if(v.begin(), v.end(),
                                  [](int x) { return x > 4; });
    std::cout << "elements > 4: " << bigCount << '\n';

    // ── 3. Generic lambda — `auto` parameters become a template operator(). ──
    auto doubleIt = [](auto x) { return x + x; };
    std::cout << "doubleIt(3)    = " << doubleIt(3)    << '\n';
    std::cout << "doubleIt(2.5)  = " << doubleIt(2.5)  << '\n';

    // ── 4. Captureless lambda → function pointer (the capture clause is empty). ──
    int (*fn)(int) = [](int x) { return x + 1; };
    std::cout << "fn(41) = " << fn(41) << '\n';
}
