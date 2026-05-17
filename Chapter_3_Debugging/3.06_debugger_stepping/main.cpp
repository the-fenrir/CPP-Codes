// 3.6 — a small program to practice stepping.
//
// sumDigits(123) should return 1+2+3 = 6. It returns the wrong value.
// Use `lldb build/3.06/main` (macOS) or `gdb build/3.06/main` (Linux):
//   b sumDigits        # break on function entry
//   run
//   n                  # step over each line; watch `n` and `sum`
//   frame variable     # (lldb)   — print all locals
//   info locals        # (gdb)
#include <iostream>

int sumDigitsBuggy(int n) {
    int sum{ 0 };
    while (n > 0) {
        sum += n % 10;
        n /= 100;            // BUG: should be /= 10, skips every other digit
    }
    return sum;
}

int sumDigitsFixed(int n) {
    int sum{ 0 };
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main() {
    std::cout << "buggy sumDigits(123)  = " << sumDigitsBuggy(123) << "  (expect 6)\n";
    std::cout << "buggy sumDigits(9876) = " << sumDigitsBuggy(9876) << "  (expect 30)\n";
    std::cout << "fixed sumDigits(123)  = " << sumDigitsFixed(123) << "  (expect 6)\n";
    std::cout << "fixed sumDigits(9876) = " << sumDigitsFixed(9876) << "  (expect 30)\n";
}
