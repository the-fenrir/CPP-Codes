// Chapter 16 quiz solutions.
//   Q1: vector definitions (compile-time check only)
//   Q2: game inventory (enum + namespace + loop)
//   Q3: min/max indices via std::pair
//   Q4: user input until -1 (driven from a stringstream for reproducible output)
//   Q5: C++man (driven from a stringstream for reproducible output)
//
// The interactive parts (Q4, Q5) are written to read from `std::istream&` so
// `make 16.x` can drive them with canned input. The same functions work with
// std::cin in real use.
#include <cassert>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// ── Q1: vector definitions ──────────────────────────────────────────
// All five lines use CTAD where useful. (b) and (c) want an explicit
// element type because the inferred type of "Alex" is `const char*`,
// not `std::string_view`; and we want `double` not `int` from `1.2`,
// which CTAD already gives us — but const-on-the-left works either way.
namespace q1 {
    std::vector            a{ 2, 4, 6, 8, 10, 12 };                       // (a)
    const std::vector      b{ 1.2, 3.4, 5.6, 7.8 };                       // (b)
    const std::vector<std::string_view> c{ "Alex", "Brad", "Charles", "Dave" }; // (c)
    std::vector            d{ 12 };                                       // (d) one elem
    std::vector<int>       e(12);                                         // (e) 12 zeros

    void demo() {
        std::cout << "Q1 sizes: "
                  << a.size() << ' ' << b.size() << ' ' << c.size() << ' '
                  << d.size() << ' ' << e.size() << '\n';
    }
}

// ── Q2: game inventory ──────────────────────────────────────────────
namespace Items {
    enum Type {
        health_potion,
        torch,
        arrow,
        max_items
    };

    constexpr std::string_view singular(Type t) {
        switch (t) {
            case health_potion: return "health potion";
            case torch:         return "torch";
            case arrow:         return "arrow";
            default:            return "?";
        }
    }
    constexpr std::string_view plural(Type t) {
        switch (t) {
            case health_potion: return "health potions";
            case torch:         return "torches";
            case arrow:         return "arrows";
            default:            return "?";
        }
    }
}

void q2() {
    std::vector inventory{ 1, 5, 10 };
    assert(std::ssize(inventory) == Items::max_items);

    int total{ 0 };
    for (int i{ 0 }; i < Items::max_items; ++i) {
        const int n{ inventory[static_cast<std::size_t>(i)] };
        const auto t{ static_cast<Items::Type>(i) };
        std::cout << "You have " << n << ' '
                  << (n == 1 ? Items::singular(t) : Items::plural(t)) << '\n';
        total += n;
    }
    std::cout << "You have " << total << " total items\n";
}

// ── Q3: min/max indices ─────────────────────────────────────────────
template <typename T>
std::pair<std::size_t, std::size_t> minMaxIndex(const std::vector<T>& v) {
    // Precondition: v is non-empty.
    std::size_t lo{ 0 }, hi{ 0 };
    for (std::size_t i{ 1 }; i < v.size(); ++i) {
        if (v[i] < v[lo]) lo = i;
        if (v[i] > v[hi]) hi = i;
    }
    return { lo, hi };
}

template <typename T>
void printArray(const std::vector<T>& v) {
    std::cout << "( ";
    for (std::size_t i{ 0 }; i < v.size(); ++i) {
        std::cout << v[i] << (i + 1 == v.size() ? " " : ", ");
    }
    std::cout << ')';
}

template <typename T>
void reportMinMax(const std::vector<T>& v) {
    std::cout << "With array ";
    printArray(v);
    std::cout << ":\n";
    if (v.empty()) {
        std::cout << "  (empty — no min/max)\n";
        return;
    }
    auto [lo, hi]{ minMaxIndex(v) };
    std::cout << "The min element has index " << lo << " and value " << v[lo] << '\n';
    std::cout << "The max element has index " << hi << " and value " << v[hi] << '\n';
}

void q3() {
    std::vector v1{ 3, 8, 2, 5, 7, 8, 3 };
    std::vector v2{ 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };
    reportMinMax(v1);
    std::cout << '\n';
    reportMinMax(v2);
}

// ── Q4: read ints until -1 ─────────────────────────────────────────
std::vector<int> readUntilSentinel(std::istream& in) {
    std::vector<int> v;
    int x{};
    while (in >> x) {
        if (x == -1) break;
        v.push_back(x);
    }
    return v;
}

void q4(std::istream& in) {
    std::cout << "Enter numbers to add (use -1 to stop): ";
    auto v{ readUntilSentinel(in) };
    // Echo the canned input back so the transcript reads naturally.
    for (int x : v) std::cout << x << ' ';
    std::cout << "-1\n";
    reportMinMax(v);
}

// ── Q5: C++man ─────────────────────────────────────────────────────
namespace WordList {
    constexpr std::string_view words[]{
        "mystery", "broccoli", "account", "almost", "spaghetti",
        "opinion", "beautiful", "distance", "luggage"
    };

    // Pick a random word (real use); the quiz driver overrides this to
    // pick "broccoli" so the output is reproducible.
    std::string_view pickRandom() {
        static std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<std::size_t> d{ 0, std::size(words) - 1 };
        return words[d(mt)];
    }
}

class Session {
    std::string_view m_word;
    std::vector<bool> m_guessed;     // 26 slots, indexed by (letter - 'a')
    int m_wrongLeft{ 6 };

    static std::size_t idx(char c) {
        // Hint from learncpp: (letter % 32) - 1 maps 'a'..'z' (or 'A'..'Z') to 0..25.
        return static_cast<std::size_t>((c % 32) - 1);
    }

public:
    explicit Session(std::string_view w) : m_word{ w }, m_guessed(26, false) {}

    bool alreadyGuessed(char c) const { return m_guessed[idx(c)]; }
    bool isInWord(char c) const { return m_word.find(c) != std::string_view::npos; }
    void recordGuess(char c) { m_guessed[idx(c)] = true; }
    void recordWrong() { --m_wrongLeft; }
    int  wrongLeft() const { return m_wrongLeft; }

    bool won() const {
        for (char c : m_word) if (!m_guessed[idx(c)]) return false;
        return true;
    }
    bool lost() const { return m_wrongLeft <= 0; }

    std::string revealed() const {
        std::string s;
        s.reserve(m_word.size());
        for (char c : m_word) s.push_back(m_guessed[idx(c)] ? c : '_');
        return s;
    }

    // Wrong guesses display: '+' for each remaining slot, followed by the
    // wrong letters in alphabetical order. e.g. "+++++a", "++++ab".
    std::string wrongDisplay() const {
        std::string s(static_cast<std::size_t>(m_wrongLeft), '+');
        for (char c{ 'a' }; c <= 'z'; ++c) {
            if (m_guessed[idx(c)] && !isInWord(c)) s.push_back(c);
        }
        return s;
    }

    std::string_view word() const { return m_word; }
};

// Read and validate a single letter from `in`. Returns 0 on EOF.
char readLetter(std::istream& in, std::ostream& out) {
    while (true) {
        out << "Enter your next letter: ";
        std::string line;
        if (!(in >> line)) return 0;
        if (line.size() == 1 &&
            ((line[0] >= 'a' && line[0] <= 'z') || (line[0] >= 'A' && line[0] <= 'Z'))) {
            // Normalize to lowercase via the `% 32` trick + offset.
            return static_cast<char>(line[0] | 0x20);
        }
        out << "That wasn't a valid input.  Try again.\n";
    }
}

void playCppman(std::istream& in, std::string_view chosenWord) {
    std::cout << "Welcome to C++man (a variant of Hangman)\n"
                 "To win: guess the word.  To lose: run out of pluses.\n\n";
    Session s{ chosenWord };
    while (!s.won() && !s.lost()) {
        std::cout << "The word: " << s.revealed()
                  << "   Wrong guesses: " << s.wrongDisplay() << '\n';
        char c{ readLetter(in, std::cout) };
        if (c == 0) { std::cout << "(EOF)\n"; return; }
        if (s.alreadyGuessed(c)) {
            std::cout << "You already guessed that.  Try again.\n";
            continue;
        }
        s.recordGuess(c);
        if (s.isInWord(c)) {
            std::cout << "Yes, '" << c << "' is in the word!\n";
        } else {
            std::cout << "No, '" << c << "' is not in the word!\n";
            s.recordWrong();
        }
        std::cout << '\n';
    }
    if (s.won()) {
        std::cout << "You won!  The word was: " << s.word() << '\n';
    } else {
        std::cout << "The word: " << s.revealed()
                  << "   Wrong guesses: " << s.wrongDisplay() << '\n';
        std::cout << "You lost!  The word was: " << s.word() << '\n';
    }
}

// ── Driver ─────────────────────────────────────────────────────────
int main() {
    std::cout << "── Q1: vector definitions ──\n";
    q1::demo();

    std::cout << "\n── Q2: inventory ──\n";
    q2();

    std::cout << "\n── Q3: min/max indices ──\n";
    q3();

    std::cout << "\n── Q4: read until -1 ──\n";
    {
        std::istringstream in{ "3 8 5 2 3 7 -1" };
        q4(in);
    }
    std::cout << "\nQ4 edge case (-1 first):\n";
    {
        std::istringstream in{ "-1" };
        q4(in);
    }

    std::cout << "\n── Q5: C++man (driven with canned guesses) ──\n";
    {
        // Canned guesses that walk through the example loss transcript.
        std::istringstream in{ "a b c d e f g h" };
        playCppman(in, "broccoli");
    }
    std::cout << "\nQ5 winning run:\n";
    {
        std::istringstream in{ "b r o c l i" };
        playCppman(in, "broccoli");
    }
}
