// 8.12 — halts: atexit handlers vs. local destructors.
//        Returning from main runs both. std::exit runs atexit but NOT
//        currently-active local destructors. We exit cleanly so the build
//        always succeeds; the std::exit line is shown commented to make
//        the difference obvious.
#include <cstdlib>
#include <iostream>

struct ScopeGuard {
    const char* name;
    ScopeGuard(const char* n) : name{ n } {
        std::cout << "  [ctor] " << name << '\n';
    }
    ~ScopeGuard() {
        std::cout << "  [dtor] " << name << '\n';
    }
};

void onExit() {
    std::cout << "  [atexit handler ran]\n";
}

int main() {
    std::atexit(onExit);
    std::cout << "main start\n";

    ScopeGuard g{ "local-in-main" };

    // ── If you uncomment this `std::exit`, the [dtor] message ABOVE would
    //    NOT print — local destructors of in-flight functions are skipped.
    //    The atexit handler still runs; static-storage destructors still run. ──
    // std::exit(EXIT_SUCCESS);

    std::cout << "main end (returning normally)\n";
    return 0;
}
