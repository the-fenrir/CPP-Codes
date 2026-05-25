// 20.7 — lambda captures: value vs. reference, mutable, init capture.
#include <iostream>
#include <memory>
#include <string>

int main() {
    // ── By-value: copy into the closure, const inside the body. ──
    int x = 10;
    auto byVal = [x]() { return x * 2; };
    x = 999;
    std::cout << "byVal()  = " << byVal()  << "  (used the captured 10)\n";

    // ── By-reference: see live state, write back. ──
    int y = 1;
    auto byRef = [&y]() { y += 1; };
    byRef(); byRef(); byRef();
    std::cout << "y after 3x byRef = " << y << '\n';

    // ── mutable: modify the *copy* held by the closure. ──
    // Each call advances the same closure's internal counter; the original is untouched.
    int seed = 100;
    auto counter = [seed]() mutable { return ++seed; };
    std::cout << "counter(): " << counter() << ' ' << counter() << ' ' << counter() << '\n';
    std::cout << "seed (outside) still = " << seed << '\n';

    // ── Init capture: move a unique_ptr into the closure (can't be done with [p]). ──
    auto greeter = [msg = std::make_unique<std::string>("hello, lambdas")]() {
        std::cout << *msg << '\n';
    };
    greeter();

    // ── Mixed capture: a fixed threshold (by value) + a live sum (by reference). ──
    int sum = 0;
    int threshold = 5;
    auto accumulateIfBig = [threshold, &sum](int n) {
        if (n > threshold) sum += n;
    };
    for (int n : { 2, 7, 4, 9, 5, 11 }) accumulateIfBig(n);
    std::cout << "sum of values > " << threshold << " = " << sum << '\n';
}
