// 27.6 — `throw;` vs `throw e;`. The first preserves the dynamic type; the
// second slices to the catch's declared type. The output proves the difference.
#include <iostream>
#include <stdexcept>

class SpecificError : public std::runtime_error {
public:
    SpecificError() : std::runtime_error{ "SpecificError::what()" } {}
};

// ── (1) bare `throw;` — preserves derived type ───────────────────────
void log_and_rethrow_correct() {
    try {
        throw SpecificError{};
    } catch (const std::exception& e) {
        std::cout << "  [inner] saw: " << e.what() << " — rethrowing with `throw;`\n";
        throw;                              // preserves SpecificError
    }
}

// ── (2) `throw e;` — slices to std::exception ────────────────────────
void log_and_rethrow_slicing() {
    try {
        throw SpecificError{};
    } catch (const std::exception& e) {
        std::cout << "  [inner] saw: " << e.what() << " — rethrowing with `throw e;`\n";
        throw e;                            // BAD: throws a std::exception copy
    }
}

int main() {
    // The outer handler asks: did we still see SpecificError?
    auto outer = [](auto fn, const char* label) {
        std::cout << label << '\n';
        try {
            fn();
        } catch (const SpecificError& e) {
            std::cout << "  [outer] caught SpecificError: " << e.what() << "\n\n";
        } catch (const std::exception& e) {
            std::cout << "  [outer] caught std::exception (SLICED): " << e.what() << "\n\n";
        }
    };

    outer(log_and_rethrow_correct, "(1) bare `throw;` — type preserved:");
    outer(log_and_rethrow_slicing, "(2) `throw e;` — type sliced:");

    return 0;
}
