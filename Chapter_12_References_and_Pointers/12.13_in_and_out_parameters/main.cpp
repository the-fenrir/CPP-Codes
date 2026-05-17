// 12.13 — in/out/return styles for the same computation.
#include <iostream>
#include <tuple>

// (a) Out-parameter style — older C-ish idiom.
void minMax_out(int a, int b, int& minOut, int& maxOut) {
    if (a < b) { minOut = a; maxOut = b; }
    else       { minOut = b; maxOut = a; }
}

// (b) Return-by-value with std::pair — modern default.
[[nodiscard]] std::pair<int,int> minMax_pair(int a, int b) {
    return (a < b) ? std::pair{ a, b } : std::pair{ b, a };
}

// (c) Return-by-value with a named struct — clearest at the call site.
struct MinMax { int min; int max; };
[[nodiscard]] MinMax minMax_struct(int a, int b) {
    return (a < b) ? MinMax{ a, b } : MinMax{ b, a };
}

int main() {
    // (a) Out-parameter: forces default-construct-then-mutate.
    int lo{}, hi{};
    minMax_out(7, 3, lo, hi);
    std::cout << "out:    min=" << lo << " max=" << hi << '\n';

    // (b) Pair: structured bindings make it readable.
    auto [p_lo, p_hi] = minMax_pair(7, 3);
    std::cout << "pair:   min=" << p_lo << " max=" << p_hi << '\n';

    // (c) Struct: named fields beat .first/.second for non-trivial returns.
    auto mm = minMax_struct(7, 3);
    std::cout << "struct: min=" << mm.min << " max=" << mm.max << '\n';

    // In/out parameter (genuinely needed): a function that updates a counter.
    int counter { 0 };
    auto bump = [](int& c) { c += 10; };
    bump(counter);
    std::cout << "counter after bump = " << counter << '\n';
}
