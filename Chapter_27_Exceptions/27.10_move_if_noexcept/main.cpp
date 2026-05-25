// 27.10 — move_if_noexcept picks move vs copy based on the move ctor's noexcept.
#include <iostream>
#include <type_traits>
#include <utility>

// Two near-identical resource holders. The ONLY difference: the move
// constructor's noexcept specification.
struct Safe {
    Safe() = default;
    Safe(const Safe&)            { std::cout << "  Safe COPY\n"; }
    Safe(Safe&&) noexcept        { std::cout << "  Safe MOVE\n"; }
};

struct Risky {
    Risky() = default;
    Risky(const Risky&)          { std::cout << "  Risky COPY\n"; }
    Risky(Risky&&) /*may throw*/ { std::cout << "  Risky MOVE\n"; }
};

// Mimic what std::vector does on reallocation: relocate via move_if_noexcept.
template <typename T>
T relocate(T& src) {
    return T{ std::move_if_noexcept(src) };
}

int main() {
    std::cout << std::boolalpha;
    std::cout << "Safe  move is noexcept?  " << std::is_nothrow_move_constructible_v<Safe>  << '\n';
    std::cout << "Risky move is noexcept?  " << std::is_nothrow_move_constructible_v<Risky> << "\n\n";

    Safe  s;
    Risky r;

    std::cout << "relocate(Safe)  -> ";
    Safe  s2 = relocate(s);   // noexcept move → moves
    (void)s2;

    std::cout << "relocate(Risky) -> ";
    Risky r2 = relocate(r);   // throwing move → falls back to copy
    (void)r2;

    std::cout << "\nTakeaway: mark your move ctor noexcept when it really is,\n"
                 "or std::vector will copy your elements when it grows.\n";
    return 0;
}
