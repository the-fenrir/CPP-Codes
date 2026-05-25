// 20.3 — recursion: base case + recursive case, with a memoization detour.
#include <iostream>
#include <unordered_map>

// Classic: factorial(0) = 1 is the base, factorial(n) = n * factorial(n-1) recurses.
int factorial(int n) {
    if (n <= 1) return 1;            // base case — must be reachable
    return n * factorial(n - 1);     // recursive case — strictly smaller input
}

// Naive Fibonacci: branches twice per call. O(2^n) — fine for n<30, painful past.
long long fibNaive(int n) {
    if (n < 2) return n;
    return fibNaive(n - 1) + fibNaive(n - 2);
}

// Memoized: cache previously computed values. O(n) calls, no recomputation.
long long fibMemo(int n, std::unordered_map<int, long long>& cache) {
    if (n < 2) return n;
    if (auto it = cache.find(n); it != cache.end()) return it->second;
    long long v = fibMemo(n - 1, cache) + fibMemo(n - 2, cache);
    cache[n] = v;
    return v;
}

// Sum-of-digits: recursion mirrors "peel off the last digit, recurse on the rest."
int sumOfDigits(int n) {
    if (n < 0) n = -n;
    if (n < 10) return n;
    return (n % 10) + sumOfDigits(n / 10);
}

int main() {
    std::cout << "5! = " << factorial(5) << '\n';
    std::cout << "10! = " << factorial(10) << '\n';

    std::cout << "fibNaive(20) = " << fibNaive(20) << '\n';

    std::unordered_map<int, long long> cache;
    std::cout << "fibMemo(50) = " << fibMemo(50, cache) << '\n';   // intractable without memo

    std::cout << "sumOfDigits(93427) = " << sumOfDigits(93427) << '\n';
}
