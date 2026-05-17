// 9.3 — semantic errors that compile cleanly but do the wrong thing.
// Each pair shows the bug (kept inert) and the fix (actually runs).
#include <cmath>
#include <iostream>

int main() {
    // ── 1. Integer division ────────────────────────────────────
    {
        const int  a{ 5 }, b{ 2 };
        const int  bug = a / b;                  // = 2     (wrong)
        const double fix = static_cast<double>(a) / b; // 2.5 (right)
        std::cout << "1. int div: bug=" << bug << "  fix=" << fix << '\n';
    }

    // ── 2. Off-by-one in a loop ────────────────────────────────
    {
        const int n{ 4 };
        int bug_count = 0;
        for (int i = 1; i < n; ++i) ++bug_count;     // iterates 3x (wrong: misses i=n)
        int fix_count = 0;
        for (int i = 1; i <= n; ++i) ++fix_count;    // iterates 4x
        std::cout << "2. off-by-one: bug=" << bug_count
                  << "  fix=" << fix_count << '\n';
    }

    // ── 3. `if (x = …)` instead of `if (x == …)` ───────────────
    {
        int x{ 0 };
        // Bug shape: `if (x = 5) { ... }` — assigns 5, always true.
        // Fix:
        if (x == 5) std::cout << "3. unreached\n";
        else        std::cout << "3. eq vs assign: x is not 5 (correct)\n";
    }

    // ── 4. Floating-point equality ─────────────────────────────
    {
        const double sum = 0.1 + 0.2;
        const bool bug = (sum == 0.3);                      // false on IEEE-754
        const bool fix = (std::abs(sum - 0.3) < 1e-9);      // true
        std::cout << "4. fp eq: bug=" << std::boolalpha << bug
                  << "  fix=" << fix << '\n';
    }

    // ── 5. Operator precedence: `x & 1 == 0` ───────────────────
    // The buggy form, `x & 1 == 0`, parses as `x & (1 == 0)` →
    // `x & 0` → 0 → false, regardless of x. We demonstrate the
    // same misparse below using explicit parentheses (which both
    // models the bug and keeps the compiler quiet under
    // -Wparentheses).
    {
        const int x{ 6 };
        const bool bug = x & (1 == 0);   // explicit form of the misparse → false
        const bool fix = (x & 1) == 0;   // "is x even?"                   → true
        std::cout << "5. precedence: bug=" << bug
                  << "  fix=" << fix << '\n';
    }

    // ── 6. Missing `break` in switch (fall-through) ────────────
    {
        const int code{ 1 };
        std::cout << "6. switch fall-through, fixed: ";
        switch (code) {
            case 1: std::cout << "one"; break;   // <-- break prevents fall-through
            case 2: std::cout << "two"; break;
            default: std::cout << "?";   break;
        }
        std::cout << '\n';
    }
}
