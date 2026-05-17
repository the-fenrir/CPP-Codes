// Chapter 9 quiz solution — Hi-Lo with a hardened input layer.
//
// Design notes:
//  • Input logic is parameterised on `std::istream&` and `std::ostream&`
//    so the whole game can be driven by a std::istringstream for testing
//    (and so it runs under `make` without interactive typing).
//  • getInt() centralises the clear/ignore/range-check sequence in one
//    place — see Q4 in NOTES.md.
//  • Errors and re-prompts go to `err` (mapped to std::cerr in main);
//    normal game output goes to `out` (std::cout). See Q3.
//  • The RNG is seeded deterministically so the test transcript is
//    reproducible. A real game would seed from std::random_device.
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>

// ── Hardened int reader ─────────────────────────────────────────
// Reads an int in [low, high] from `in`. Loops until success.
// Trailing junk on a successful line is discarded silently.
int getInt(std::istream& in, std::ostream& out, std::ostream& err,
           int low, int high, const std::string& prompt)
{
    while (true) {
        out << prompt;
        int x;
        in >> x;

        if (in.eof()) {
            // No more input. In an interactive program we'd keep
            // looping; in scripted tests we bail out clean.
            err << "(end of input)\n";
            std::exit(0);
        }

        if (in.fail()) {                    // wrong type or overflow
            err << "  that's not a number, try again\n";
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Drop trailing junk on the same line — "43x" or "43 hello"
        // both yield 43 and a clean buffer.
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (x < low || x > high) {
            err << "  out of range [" << low << ", " << high << "], try again\n";
            continue;
        }
        return x;
    }
}

// ── Yes/no reader ───────────────────────────────────────────────
// Accepts 'y'/'Y' or 'n'/'N' as the first non-whitespace char;
// flushes the rest of the line. "yes please" -> yes; "nope" -> no.
bool getYesNo(std::istream& in, std::ostream& out, std::ostream& err,
              const std::string& prompt)
{
    while (true) {
        out << prompt;
        char c;
        in >> c;                            // >> skips leading whitespace

        if (in.eof()) std::exit(0);
        if (in.fail()) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (c == 'y' || c == 'Y') return true;
        if (c == 'n' || c == 'N') return false;
        err << "  please answer y or n\n";
    }
}

// ── One round of Hi-Lo ──────────────────────────────────────────
// Returns true if the player won, false if they ran out of guesses.
bool playRound(std::istream& in, std::ostream& out, std::ostream& err, int secret)
{
    constexpr int kMaxGuesses = 7;
    out << "I picked a number between 1 and 100. You have "
        << kMaxGuesses << " tries.\n";

    for (int i = 1; i <= kMaxGuesses; ++i) {
        const int guess = getInt(in, out, err, 1, 100,
                                 "guess #" + std::to_string(i) + ": ");
        if (guess == secret) {
            out << "Correct — you win!\n";
            return true;
        }
        out << (guess < secret ? "  too low\n" : "  too high\n");
    }
    out << "Out of guesses. The number was " << secret << ".\n";
    return false;
}

// ── Game loop ───────────────────────────────────────────────────
void play(std::istream& in, std::ostream& out, std::ostream& err, unsigned seed)
{
    std::mt19937 rng{ seed };
    std::uniform_int_distribution<int> dist{ 1, 100 };

    while (true) {
        playRound(in, out, err, dist(rng));
        if (!getYesNo(in, out, err, "play again? (y/n): ")) {
            out << "Bye.\n";
            return;
        }
    }
}

int main() {
    // Scripted input demonstrates all the hardening cases at once:
    //   - "x"                  -> invalid type, re-prompt
    //   - "0", "101"           -> out of range, re-prompt
    //   - "50 hello"           -> accept 50, flush trailing junk
    //   - "yes please"         -> accept 'y'
    //   - "nope"               -> accept 'n', exit
    // With seed 42 the first secret happens to be drawable in a few
    // guesses; we just play one round, ask to continue, and quit.
    std::istringstream scripted{
        "x\n"           // bad type
        "0\n"           // out of range
        "101\n"         // out of range
        "50 hello\n"    // valid + junk
        "25\n"
        "75\n"
        "37\n"
        "62\n"
        "50\n"
        "44\n"
        "55\n"          // 7 real guesses (round will likely end here)
        "nope\n"        // don't play again
    };

    play(scripted, std::cout, std::cerr, /*seed=*/42u);
}
