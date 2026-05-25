// 27.9 — noexcept as both a specifier (contract) and an operator (query).
#include <iostream>
#include <stdexcept>

// Two functions with opposite contracts:
void may_throw()        { /* could throw, doesn't promise otherwise */ }
void never_throws() noexcept { /* contract: nothing escapes */ }

// A template function that propagates the noexcept of its callable.
// noexcept(noexcept(f())) is the C++ idiom for "noexcept iff f() is noexcept".
template <typename F>
void call(F f) noexcept(noexcept(f())) {
    f();
}

int main() {
    // The noexcept operator: a constexpr bool, not a call.
    std::cout << std::boolalpha;
    std::cout << "noexcept(may_throw())    = " << noexcept(may_throw())    << '\n';
    std::cout << "noexcept(never_throws()) = " << noexcept(never_throws()) << '\n';

    // call<F> picks up the F's noexcept property:
    std::cout << "noexcept(call(may_throw))    = " << noexcept(call(may_throw))    << '\n';
    std::cout << "noexcept(call(never_throws)) = " << noexcept(call(never_throws)) << '\n';

    // We intentionally do NOT demonstrate a noexcept-violation; that would
    // call std::terminate and fail the build harness. The contract is real:
    // if `never_throws` ever threw, the program would abort here.
    std::cout << "all queries succeeded\n";
    return 0;
}
