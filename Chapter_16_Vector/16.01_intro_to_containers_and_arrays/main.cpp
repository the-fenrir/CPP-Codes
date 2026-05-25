// 16.1 — one variable per value vs. a container holding many values of one type.
#include <iostream>
#include <vector>

int main() {
    // Without a container: one named variable per score. Doesn't scale.
    int s0{ 84 };
    int s1{ 92 };
    int s2{ 76 };
    std::cout << "Three separate ints: " << s0 << ' ' << s1 << ' ' << s2 << '\n';

    // With a container: one named object holding many values, accessed by index.
    std::vector<int> scores{ 84, 92, 76, 88, 95 };

    std::cout << "Vector length: " << scores.size() << '\n';
    std::cout << "scores[0] = " << scores[0] << '\n';
    std::cout << "scores[" << scores.size() - 1 << "] = "
              << scores[scores.size() - 1] << '\n';
}
