// Chapter 6 quiz solution.
//   Q1: getQuantityPhrase + getApplesPluralized, demonstrating both
//       sequential if/else and the conditional operator.
#include <iostream>
#include <string_view>

// ── getQuantityPhrase ──────────────────────────────────────────────
//
// Design notes:
//  • Return type is std::string_view, not std::string. Every return value
//    is a string literal (static storage, lives forever), so there is no
//    ownership to transfer — a view is cheap and never copies. If you ever
//    return a temporary std::string from a function with this signature,
//    the view will dangle; only return literals or members with matching
//    lifetimes.
//  • A flat if/else-if chain is the clearest expression of "match against
//    a range." Trying to encode all six branches as nested ternaries would
//    score points for cleverness and lose them for legibility.
std::string_view getQuantityPhrase(int quantity)
{
    if (quantity < 0) return "negative";
    if (quantity == 0) return "no";
    if (quantity == 1) return "a single";
    if (quantity == 2) return "a couple of";
    if (quantity == 3) return "a few";
    return "many";
}

// ── getApplesPluralized ────────────────────────────────────────────
//
// Design notes:
//  • The spec requires the conditional operator here — and this is the
//    textbook good fit: a single-decision pick between two string
//    literals, used inline in a return.
//  • Parenthesize the condition for readability even though precedence
//    doesn't strictly require it.
std::string_view getApplesPluralized(int quantity)
{
    return (quantity == 1) ? "apple" : "apples";
}

static void report(std::string_view who, int quantity)
{
    std::cout << who << " has "
              << getQuantityPhrase(quantity) << ' '
              << getApplesPluralized(quantity) << ".\n";
}

int main()
{
    // The learncpp version reads `quantity` from std::cin. We hard-code
    // the two example inputs so the build is non-interactive and the
    // expected output reproduces exactly.
    report("Mary", 3);

    int yours{ 1 };
    std::cout << "How many apples do you have? " << yours << '\n';
    std::cout << "You have "
              << getQuantityPhrase(yours) << ' '
              << getApplesPluralized(yours) << ".\n";

    // A couple of extra cases to exercise every branch.
    report("Bob",   -2);
    report("Cara",   0);
    report("Dave",   2);
    report("Eve",  100);
}
