// 16.5 — return by value is cheap: NRVO elides, otherwise std::vector moves.
#include <iostream>
#include <utility>
#include <vector>

// Factory: build and return. With NRVO, no copy or move actually happens.
std::vector<int> makeSquares(int n) {
    std::vector<int> result;
    result.reserve(static_cast<std::size_t>(n));
    for (int i{ 1 }; i <= n; ++i) result.push_back(i * i);
    return result;  // NOT `return std::move(result);` — that would disable NRVO.
}

int main() {
    std::vector<int> v{ makeSquares(5) };
    std::cout << "v: ";
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';

    // Explicit move: transfer guts from v into w. v is left empty (but valid).
    std::vector<int> w{ std::move(v) };
    std::cout << "after std::move(v):\n";
    std::cout << "  w.size() = " << w.size() << '\n';
    std::cout << "  v.size() = " << v.size() << "  (moved-from: empty)\n";
}
