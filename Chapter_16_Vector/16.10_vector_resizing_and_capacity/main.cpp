// 16.10 — size vs. capacity; reserve() prevents repeated reallocation.
#include <iostream>
#include <vector>

void report(const char* label, const std::vector<int>& v) {
    std::cout << label
              << " size=" << v.size()
              << " capacity=" << v.capacity() << '\n';
}

int main() {
    std::cout << "── push_back without reserve ──\n";
    std::vector<int> a;
    report("start", a);
    for (int i{ 0 }; i < 8; ++i) {
        a.push_back(i);
        report(" push", a);  // capacity jumps in chunks (impl-defined growth)
    }

    std::cout << "\n── push_back with reserve ──\n";
    std::vector<int> b;
    b.reserve(8);
    report("after reserve(8)", b);  // size still 0, capacity ≥ 8
    for (int i{ 0 }; i < 8; ++i) {
        b.push_back(i);
        report(" push", b);  // capacity stays put; no reallocation
    }

    std::cout << "\n── resize changes size ──\n";
    std::vector<int> c{ 1, 2, 3 };
    report("before", c);
    c.resize(6);
    report("resize(6)", c);  // grew; new elements default-initialized to 0
    c.resize(2);
    report("resize(2)", c);  // shrunk; capacity may be unchanged
}
