// 9.5 — handling invalid input.
// We feed scripted input through a std::istringstream rather than
// std::cin so the program runs non-interactively under `make`. The
// extraction/clear/ignore logic is identical to what you'd write
// against std::cin.
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

// Read one int from `in`, retrying on failure. Returns when a clean
// int is consumed *and* the rest of the line is flushed. The boolean
// in the return tracks whether we ever recovered from a failure (for
// the demo printout).
template <typename Stream>
int readInt(Stream& in, const std::string& label) {
    while (true) {
        int x;
        in >> x;

        if (in.fail()) {                          // junk or overflow
            std::cout << "  [" << label << "] extraction failed; recovering\n";
            in.clear();                           // reset error flags
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;                             // re-prompt
        }

        // Success: also flush trailing junk on the same line
        // (handles "5 abc" -> we keep 5, drop " abc").
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [" << label << "] got " << x << '\n';
        return x;
    }
}

int main() {
    // Scripted input — pretend the user typed these lines in order.
    //   line 1: junk         → fail, then retry…
    //   line 2: a valid int  → consumed
    //   line 3: int + junk   → 7 kept, trailing junk flushed
    //   line 4: overflowing  → fail, then retry…
    //   line 5: valid int    → consumed
    std::istringstream scripted{
        "abc\n"
        "42\n"
        "7 trailing junk\n"
        "99999999999999999999\n"
        "-3\n"
    };

    std::cout << "── case 1: junk then valid ──\n";
    readInt(scripted, "first");

    std::cout << "\n── case 2: valid + trailing junk on same line ──\n";
    readInt(scripted, "second");

    std::cout << "\n── case 3: overflow then valid ──\n";
    readInt(scripted, "third");
}
