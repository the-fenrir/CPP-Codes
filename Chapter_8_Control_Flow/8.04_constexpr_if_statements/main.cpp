// 8.4 — `if constexpr` discards the not-taken branch at compile time.
//
// Each branch below uses an operation that's only valid for one of the type
// categories (modulo for ints, std::is_nan-style ops for floats). A regular
// `if` would fail to compile because every branch must be valid for T.
#include <cmath>
#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
void describe(T value) {
    if constexpr (std::is_integral_v<T>) {
        // Modulo only makes sense for integral types — invalid for double.
        std::cout << "int  " << value << " (parity: "
                  << (value % 2 == 0 ? "even" : "odd") << ")\n";
    } else if constexpr (std::is_floating_point_v<T>) {
        // std::floor doesn't accept std::string — branch discarded for other T.
        std::cout << "flt  " << value << " (floor: " << std::floor(value) << ")\n";
    } else {
        // Fallback for things that are neither integral nor floating-point.
        std::cout << "other " << value << "\n";
    }
}

int main() {
    describe(42);            // → integral branch
    describe(3.75);          // → floating-point branch
    describe(std::string{ "hello" }); // → fallback branch

    // Quick demo with a compile-time-known integer condition (no template):
    // the not-taken branch is discarded; the binary contains only the "yes" line.
    constexpr bool debug = true;
    if constexpr (debug)
        std::cout << "[debug build]\n";
    else
        std::cout << "[release build]\n";
}
