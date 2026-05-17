// 6.6 — the conditional operator: where it shines, where it doesn't.
#include <iostream>
#include <string_view>

int main() {
    int a{ 3 }, b{ 7 };

    // ── classic: pick a value ───────────────────────────────────
    int larger = (a > b) ? a : b;
    std::cout << "max(" << a << ',' << b << ") = " << larger << '\n';

    // ── const init that an if-statement can't easily do ─────────
    const bool weekend{ true };
    const int hours = weekend ? 0 : 8;     // const + conditional init in one line
    std::cout << "hours worked today: " << hours << '\n';

    // ── inline in stream insertion (must parenthesize) ──────────
    int n{ 1 };
    std::cout << "you have " << n << ' '
              << (n == 1 ? "apple" : "apples") << '\n';

    n = 3;
    std::cout << "you have " << n << ' '
              << (n == 1 ? "apple" : "apples") << '\n';

    // ── readable nesting (still: prefer if/else past one level) ─
    int score{ 72 };
    std::string_view grade =
          (score >= 90) ? "A"
        : (score >= 80) ? "B"
        : (score >= 70) ? "C"
        : (score >= 60) ? "D"
        : "F";
    std::cout << "grade for " << score << ": " << grade << '\n';
}
