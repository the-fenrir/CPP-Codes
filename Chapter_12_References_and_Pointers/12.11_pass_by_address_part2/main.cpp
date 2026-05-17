// 12.11 — pass-by-address design: optional input, optional output, repointing.
#include <iostream>
#include <string>

// (1) Optional input: caller may pass nullptr if they don't want logging.
void doWork(int input, std::string* log = nullptr) {
    if (log) *log += "doWork called with " + std::to_string(input) + '\n';
}

// (2) Optional output: caller passes &out to receive, or nullptr to skip.
bool tryParseInt(const std::string& s, int* out) {
    try {
        int v = std::stoi(s);
        if (out) *out = v;
        return true;
    } catch (...) {
        return false;
    }
}

// (3) Repoint the caller's pointer: needs T*& (or T**).
//     Plain T* would only rebind the local parameter and surprise the caller.
void rebindToY(int*& p, int& y) {
    p = &y;
}

int main() {
    // (1) Optional input
    std::string log;
    doWork(1);                       // no logging
    doWork(2, &log);                 // logging on
    std::cout << "log:\n" << log;

    // (2) Optional output
    int parsed{};
    if (tryParseInt("42", &parsed))   std::cout << "parsed = " << parsed << '\n';
    if (tryParseInt("nope", nullptr)) std::cout << "(would not print)\n";
    else                              std::cout << "second parse failed (expected)\n";

    // (3) Repoint
    int x { 1 }, y { 2 };
    int* p { &x };
    std::cout << "before rebindToY: *p = " << *p << '\n';
    rebindToY(p, y);                  // T*& — actually changes p
    std::cout << "after  rebindToY: *p = " << *p << '\n';
}
