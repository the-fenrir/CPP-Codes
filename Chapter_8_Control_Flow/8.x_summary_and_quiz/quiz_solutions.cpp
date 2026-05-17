// Chapter 8 quiz solutions.
//   Q1: ball drop until ground — while loop + namespace + constexpr
//   Q2: isPrime via for loop (with the sqrt + odd-only extra-credit version)
//   Q3: Hi-Lo guessing game with input validation (simulated input)
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>
#include <string>

// ── Q1: Ball drop ───────────────────────────────────────────────────────────
//
// Design notes:
//  • Constants go in a namespace and are `constexpr` — single source of truth,
//    available at compile time, no risk of someone modifying them.
//  • The helper returns the *current* height. Loop terminates when it returns
//    a non-positive value: that's the contract.
//  • The loop is a `while`, not a `for`, because the step (time advancing) and
//    the exit condition (height hit zero) aren't naturally co-located.
namespace Ball {
    constexpr double gravity{ 9.8 };          // m/s²

    // Returns the height at time t, floored at 0. Side-effects: prints height.
    double calculateAndPrintBallHeight(double initialHeight, int seconds) {
        const double distanceFallen = (gravity * seconds * seconds) / 2.0;
        double height{ initialHeight - distanceFallen };

        if (height > 0.0) {
            std::cout << "  At " << seconds << " s, the ball is at "
                      << height << " m\n";
        } else {
            height = 0.0;
            std::cout << "  At " << seconds << " s, the ball is on the ground.\n";
        }
        return height;
    }
}

void runBallDrop() {
    std::cout << "── Q1: ball drop ──\n";
    constexpr double initialHeight{ 100.0 };
    int seconds{ 0 };
    double height{ initialHeight };
    while (height > 0.0) {
        height = Ball::calculateAndPrintBallHeight(initialHeight, seconds);
        ++seconds;
    }
}

// ── Q2: isPrime ─────────────────────────────────────────────────────────────
//
// Design notes:
//  • Numbers < 2 are not prime — handle that first; the loop below assumes x >= 2.
//  • 2 is the only even prime — special-case it so we can skip all even
//    divisors afterwards.
//  • Test only odd divisors up to sqrt(x). If x has a factor f > sqrt(x), then
//    x/f < sqrt(x) and we'd have already found that smaller factor.
//  • `i * i <= x` is preferred over `i <= std::sqrt(x)` to avoid a float
//    conversion and a tiny precision worry — and to keep this `constexpr`-able
//    if you needed to later.
bool isPrime(int x) {
    if (x < 2)        return false;
    if (x == 2)       return true;
    if (x % 2 == 0)   return false;

    for (int i = 3; i * i <= x; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

void runPrimeTests() {
    std::cout << "── Q2: isPrime ──\n";
    assert(!isPrime(0));
    assert(!isPrime(1));
    assert( isPrime(2));
    assert( isPrime(3));
    assert(!isPrime(4));
    assert( isPrime(5));
    assert( isPrime(7));
    assert(!isPrime(9));
    assert( isPrime(11));
    assert( isPrime(13));
    assert(!isPrime(15));
    assert( isPrime(13417));
    std::cout << "  all asserts passed.\n";
}

// ── Q3: Hi-Lo game ──────────────────────────────────────────────────────────
//
// Design notes:
//  • `Random` namespace mirrors 8.15 — one shared engine, inlined here so the
//    quiz file is standalone (no Random.h to include).
//  • The game loop is bounded by `guesses` (do-while with a manual counter
//    would also work; a for is more readable when the upper bound is known).
//  • playAgain() validates input with a do-while + switch — exactly the input
//    validation pattern from 8.9. We simulate the input from a fixed array so
//    the build is reproducible.
//  • In the real game you'd read from std::cin. For the worked solution we
//    drive guesses with two scripted scenarios: one win, one loss.
namespace Random {
    inline std::mt19937 mt{ std::random_device{}() };
    inline int get(int min, int max) {
        std::uniform_int_distribution<int> dist{ min, max };
        return dist(mt);
    }
}

constexpr int kMaxGuesses{ 7 };

// Single round. Returns true if the player wins, false if they run out.
bool playRound(int secret, const int* guesses, int numGuesses) {
    std::cout << "  (secret is " << secret << " — visible here only because we"
                 " script the inputs)\n";
    for (int g = 0; g < kMaxGuesses && g < numGuesses; ++g) {
        const int guess = guesses[g];
        std::cout << "  guess " << (g + 1) << ": " << guess << " — ";
        if (guess == secret) {
            std::cout << "correct!\n";
            return true;
        } else if (guess < secret) {
            std::cout << "too low\n";
        } else {
            std::cout << "too high\n";
        }
    }
    std::cout << "  out of guesses. Secret was " << secret << ".\n";
    return false;
}

// "y" or "n" only; re-prompts on anything else. Scripted answers here.
bool playAgain(const char* scripted) {
    int i = 0;
    while (true) {
        const char c = scripted[i++];
        std::cout << "  play again? > " << c << '\n';
        switch (c) {
            case 'y': case 'Y': return true;
            case 'n': case 'N': return false;
            default:
                std::cout << "    invalid; try again.\n";
                break;
        }
    }
}

void runHiLo() {
    std::cout << "── Q3: Hi-Lo ──\n";

    // Game 1: secret 42, guesses follow a binary-search-ish pattern → win on #5.
    {
        constexpr int secret{ 42 };
        const int guesses[] = { 50, 25, 38, 44, 42 };
        std::cout << "Game 1:\n";
        playRound(secret, guesses, 5);
    }

    // Game 2: secret 73, only 4 wrong guesses fit in 7 tries → loss.
    {
        constexpr int secret{ 73 };
        const int guesses[] = { 50, 10, 20, 30, 40, 60, 70 };
        std::cout << "Game 2:\n";
        playRound(secret, guesses, 7);
    }

    // Play-again prompt with garbage input first, then "n".
    std::cout << "Play-again validation:\n";
    const char scripted[] = { 'x', '?', 'n' };
    const bool again = playAgain(scripted);
    std::cout << "  decision: " << (again ? "yes" : "no") << '\n';
}

int main() {
    runBallDrop();
    std::cout << '\n';
    runPrimeTests();
    std::cout << '\n';
    runHiLo();
}
