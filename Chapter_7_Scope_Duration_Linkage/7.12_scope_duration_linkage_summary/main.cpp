// 7.12 — one example of each scope/duration/linkage combination.
#include <iostream>

// namespace scope, static duration, external linkage.
int g_external{ 1 };

// namespace scope, static duration, internal linkage.
static int g_internal{ 2 };

// namespace scope, static duration, internal linkage (const default).
const int g_const{ 3 };

// namespace scope, static duration, external linkage (inline ⇒ one defn).
inline constexpr int g_inline{ 4 };

void demo() {
    int local{ 10 };                // block, automatic, no linkage
    static int s_local{ 20 };       // block, static,    no linkage
    ++s_local;

    std::cout << "  local      = " << local      << "  (block / auto / none)\n";
    std::cout << "  s_local    = " << s_local    << "  (block / static / none)\n";
    std::cout << "  g_external = " << g_external << "  (ns / static / external)\n";
    std::cout << "  g_internal = " << g_internal << "  (ns / static / internal)\n";
    std::cout << "  g_const    = " << g_const    << "  (ns / static / internal)\n";
    std::cout << "  g_inline   = " << g_inline   << "  (ns / static / external)\n";
}

int main() {
    std::cout << "call 1:\n"; demo();
    std::cout << "call 2:\n"; demo();
    std::cout << "(notice s_local survives across calls; local does not)\n";
}
