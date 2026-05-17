// 8.7 — `goto` to break out of nested loops, vs. the refactor that doesn't need it.
#include <iostream>
#include <optional>

// ── With goto: jump out of two loops to a shared label ──
std::optional<std::pair<int,int>> findGoto(int target) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i * 10 + j == target)
                goto found;            // forward jump out of nested loop
        }
    }
    return std::nullopt;

found:
    // We can't tell from this label which i,j matched — that's a real readability
    // problem with goto. The refactor below doesn't have it.
    return std::nullopt; // placeholder — see refactor for the real answer
}

// ── Refactor: extract the inner loop into a function that just returns ──
//   When `return` lives inside the inner work, "break out of everything" is free.
std::optional<std::pair<int,int>> findClean(int target) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i * 10 + j == target)
                return std::pair{ i, j };  // exits both loops, keeps i/j
        }
    }
    return std::nullopt;
}

int main() {
    auto a = findGoto(23);
    std::cout << "findGoto(23):  " << (a ? "found-(no i,j)" : "not found") << '\n';

    auto b = findClean(23);
    if (b) std::cout << "findClean(23): " << b->first << ',' << b->second << '\n';
    else   std::cout << "findClean(23): not found\n";
}
