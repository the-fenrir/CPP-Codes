// 17.11 — three ways to name a fixed string, three sets of trade-offs.
#include <iostream>
#include <string_view>

// Modern best practice: header-includable compile-time constant.
inline constexpr std::string_view kGreeting { "hello" };

int main() {
    // 1) Array — local copy of the literal, writable, sizeof = length+1.
    char asArray[] { "hello" };
    asArray[0] = 'H';     // legal — it's our copy
    std::cout << "asArray   = " << asArray
              << "   sizeof = " << sizeof(asArray) << '\n';

    // 2) Pointer to string literal — points into read-only storage.
    const char* asPtr { "hello" };
    // asPtr[0] = 'H';    // UB — modifying a string literal
    std::cout << "asPtr     = " << asPtr
              << "   sizeof = " << sizeof(asPtr) << " (pointer)\n";

    // 3) string_view — modern alternative. No allocation, knows its length,
    //    safe to copy and slice.
    std::cout << "kGreeting = " << kGreeting
              << "   size   = " << kGreeting.size() << '\n';

    // string_view comparisons are value-based, unlike `const char*`:
    constexpr std::string_view other { "hello" };
    static_assert(kGreeting == other);
}
