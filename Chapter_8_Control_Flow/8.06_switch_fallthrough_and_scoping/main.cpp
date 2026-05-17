// 8.6 — deliberate fallthrough with [[fallthrough]], multi-label cases, and
//        per-case scoping with braces.
#include <iostream>

void multi(int n) {
    // ── Multi-label case: same body for several values. Not fallthrough. ──
    switch (n) {
        case 1:
        case 2:
        case 3:
            std::cout << "small\n";
            break;
        case 4:
        case 5:
            std::cout << "medium\n";
            break;
        default:
            std::cout << "other\n";
            break;
    }
}

void deliberate(int n) {
    // ── Intentional fallthrough: case 2 runs case 3's body too. Mark it. ──
    switch (n) {
        case 1:
            std::cout << "one ";
            break;
        case 2:
            std::cout << "two-then- ";
            [[fallthrough]];   // <-- explicit; required to silence the warning
        case 3:
            std::cout << "three\n";
            break;
        default:
            std::cout << "other\n";
            break;
    }
}

void scoped(int n) {
    // ── Each case gets its own { } block, so `msg` belongs to exactly one case. ──
    switch (n) {
        case 1: {
            const char* msg{ "one" };
            std::cout << msg << '\n';
            break;
        }
        case 2: {
            const char* msg{ "two" };     // independent variable, same name OK
            std::cout << msg << '\n';
            break;
        }
        default:
            std::cout << "other\n";
            break;
    }
}

int main() {
    std::cout << "── multi-label ──\n";
    for (int n : { 1, 2, 4, 9 }) multi(n);

    std::cout << "── deliberate fallthrough ──\n";
    for (int n : { 1, 2, 3 }) deliberate(n);

    std::cout << "── per-case scope ──\n";
    for (int n : { 1, 2, 7 }) scoped(n);
}
