// 3.2 — walk this through the five-step process.
//
// Symptom: average of {1,2,3,4,5} should be 3.0, but this prints 3.
// Step 1 (root cause): both operands of `/` are int → integer division.
// Step 2 (why):        3 fits exactly, so we'd miss it; try {1,2,3,4} → 2.5
//                      becomes 2. Same root cause.
// Step 3 (options):    (a) cast sum to double, (b) make sum a double,
//                      (c) cast count, (d) use 5.0 literal somewhere.
//                      Pick (b) — fewest moving parts, clearest intent.
// Step 4: see `averageFixed` below.
// Step 5: retest with {1,2,3,4} → expect 2.5, not 2.
#include <iostream>
#include <vector>

double averageBuggy(const std::vector<int>& v) {
    int sum{ 0 };
    for (int x : v) sum += x;
    return sum / v.size();           // BUG: int / size_t → integer division
}

double averageFixed(const std::vector<int>& v) {
    double sum{ 0.0 };               // fix: accumulate in double
    for (int x : v) sum += x;
    return sum / static_cast<double>(v.size());
}

int main() {
    std::vector<int> a{ 1, 2, 3, 4, 5 };
    std::vector<int> b{ 1, 2, 3, 4 };

    std::cout << "buggy avg(1..5) = " << averageBuggy(a) << "   (expect 3)\n";
    std::cout << "buggy avg(1..4) = " << averageBuggy(b) << "   (expect 2.5)\n";
    std::cout << "fixed avg(1..5) = " << averageFixed(a) << "   (expect 3)\n";
    std::cout << "fixed avg(1..4) = " << averageFixed(b) << "   (expect 2.5)\n";
}
