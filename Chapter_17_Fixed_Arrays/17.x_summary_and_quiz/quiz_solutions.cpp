// Chapter 17 quiz solutions.
//
//   Q1a/b/c — fixes for the three buggy snippets.
//   Q2      — Roscoe's potion emporium (input scripted via stringstream).
//   Q3/Q4   — card deck + a single round of blackjack, with flexible aces (Q5).
//   Q5 also has a discussion answer in NOTES.md.
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

// ── Q1a: off-by-one fix ─────────────────────────────────────────────
//
// Original used `count <= std::size(arr)` and overran. `<` is the fix.
void q1a() {
    std::cout << "── Q1a ──\n";
    std::array arr { 0, 1, 2, 3 };
    for (std::size_t count { 0 }; count < std::size(arr); ++count)
        std::cout << arr[count] << ' ';
    std::cout << '\n';
}

// ── Q1b: decay broke the range-for ──────────────────────────────────
//
// Original passed a C-style array; the parameter `int array[]` is `int*`,
// which has no begin()/end(). Switching to std::array kills the decay.
template <std::size_t N>
static void printArray(const std::array<int, N>& a) {
    for (int x : a) std::cout << x << ' ';
    std::cout << '\n';
}
void q1b() {
    std::cout << "── Q1b ──\n";
    std::array arr { 9, 7, 5, 3, 1 };
    printArray(arr);
}

// ── Q1c: runtime size requires std::vector ──────────────────────────
//
// std::array<int, length> requires `length` to be a constant expression.
// When the size comes from input, you need a vector. Inputs scripted for
// reproducibility.
void q1c() {
    std::cout << "── Q1c ──\n";
    std::istringstream in { "3\n10 20 30\n" };
    std::size_t length {};
    in >> length;
    std::vector<int> scores(length);
    for (std::size_t i { 0 }; i < length; ++i) in >> scores[i];
    std::cout << length << " scores entered:";
    for (int s : scores) std::cout << ' ' << s;
    std::cout << '\n';
}

// ── Q2: Roscoe's potion emporium ────────────────────────────────────
namespace Potion {
    enum Type {
        healing,
        mana,
        speed,
        invisibility,
        max_potions,
    };
    constexpr std::array<std::string_view, max_potions> name {
        "healing", "mana", "speed", "invisibility"
    };
    constexpr std::array<int, max_potions> cost { 20, 30, 12, 50 };

    static_assert(std::size(name) == max_potions);
    static_assert(std::size(cost) == max_potions);
}

static void shop() {
    std::cout << "\nHere is our selection for today:\n";
    for (int p { 0 }; p < Potion::max_potions; ++p)
        std::cout << p << ") " << Potion::name[p]
                  << " costs " << Potion::cost[p] << '\n';
}

class Player {
    std::string m_name;
    int m_gold;
    std::array<int, Potion::max_potions> m_inventory {};   // zero-init
public:
    Player(std::string name, int gold) : m_name { std::move(name) }, m_gold { gold } {}

    const std::string& name()  const { return m_name; }
    int                gold()  const { return m_gold; }

    // Returns true on success (gold debited, inventory incremented).
    bool buy(Potion::Type p) {
        if (m_gold < Potion::cost[p]) return false;
        m_gold -= Potion::cost[p];
        ++m_inventory[p];
        return true;
    }

    void summarizeInventory() const {
        std::cout << "Your inventory contains:\n";
        bool any { false };
        for (int p { 0 }; p < Potion::max_potions; ++p) {
            if (m_inventory[p] > 0) {
                std::cout << "  " << m_inventory[p]
                          << "x potion of " << Potion::name[p] << '\n';
                any = true;
            }
        }
        if (!any) std::cout << "  (nothing)\n";
        std::cout << "You escaped with " << m_gold << " gold remaining.\n";
    }
};

// Run one shopping session reading commands from `in`.
static void runEmporium(std::istream& in, Player& player) {
    std::cout << "Welcome to Roscoe's potion emporium!\n";
    std::cout << "Hello, " << player.name()
              << ", you have " << player.gold() << " gold.\n";

    while (true) {
        shop();
        std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";
        std::string token;
        if (!(in >> token)) break;
        std::cout << token << '\n';   // echo scripted input

        if (token == "q" || token == "Q") break;

        // Try to parse as int and validate the range.
        int n { -1 };
        try {
            std::size_t pos {};
            n = std::stoi(token, &pos);
            if (pos != token.size()) n = -1;
        } catch (...) {
            n = -1;
        }
        if (n < 0 || n >= Potion::max_potions) {
            std::cout << "That is an invalid input.\n";
            continue;
        }

        const auto p { static_cast<Potion::Type>(n) };
        if (player.buy(p))
            std::cout << "You purchased a potion of " << Potion::name[p]
                      << ".  You have " << player.gold() << " gold left.\n";
        else
            std::cout << "You can't afford that.\n";
    }

    player.summarizeInventory();
    std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";
}

void q2() {
    std::cout << "── Q2: Roscoe's potion emporium ──\n";
    // Scripted input: invalid token, then buy 3, buy 2, buy 2, quit.
    std::istringstream in { "a 3 2 2 q\n" };
    Player alex { "Alex", 85 };   // fixed gold for reproducible output
    runEmporium(in, alex);
}

// ── Q3: Card / Deck ─────────────────────────────────────────────────
namespace Cards {
    enum Rank {
        ace, two, three, four, five, six, seven,
        eight, nine, ten, jack, queen, king,
        max_ranks,
    };
    enum Suit {
        clubs, diamonds, hearts, spades,
        max_suits,
    };

    struct Card {
        Rank rank;
        Suit suit;

        // Score with ace = 11 by default; the blackjack code demotes later.
        int value() const {
            switch (rank) {
            case ace:                                       return 11;
            case two:                                       return 2;
            case three:                                     return 3;
            case four:                                      return 4;
            case five:                                      return 5;
            case six:                                       return 6;
            case seven:                                     return 7;
            case eight:                                     return 8;
            case nine:                                      return 9;
            case ten: case jack: case queen: case king:     return 10;
            default:                                        return 0;
            }
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Card& c) {
        static constexpr std::array<char, max_ranks> rankCh {
            'A','2','3','4','5','6','7','8','9','T','J','Q','K'
        };
        static constexpr std::array<char, max_suits> suitCh {
            'C','D','H','S'
        };
        return os << rankCh[c.rank] << suitCh[c.suit];
    }

    class Deck {
        std::array<Card, max_ranks * max_suits> m_cards;
        std::size_t m_nextDeal { 0 };
    public:
        Deck() {
            std::size_t i { 0 };
            for (int s { 0 }; s < max_suits; ++s)
                for (int r { 0 }; r < max_ranks; ++r)
                    m_cards[i++] = Card{ static_cast<Rank>(r),
                                         static_cast<Suit>(s) };
        }

        void shuffle(std::mt19937& rng) {
            std::shuffle(m_cards.begin(), m_cards.end(), rng);
            m_nextDeal = 0;
        }

        Card dealCard() { return m_cards[m_nextDeal++]; }
    };
}

// ── Q4 + Q5: one round of blackjack with flexible aces ──────────────
namespace Blackjack {
    using namespace Cards;

    // Score a hand: count aces, total with aces at 11, then demote
    // aces to 1 while we're over 21.
    static int score(const std::vector<Card>& hand) {
        int total { 0 };
        int aces  { 0 };
        for (const Card& c : hand) {
            total += c.value();
            if (c.rank == ace) ++aces;
        }
        while (total > 21 && aces > 0) {
            total -= 10;
            --aces;
        }
        return total;
    }

    static void show(std::string_view who, const std::vector<Card>& hand) {
        std::cout << who << ":";
        for (const Card& c : hand) std::cout << ' ' << c;
        std::cout << "  (score " << score(hand) << ")\n";
    }

    // Player stands at 17+; dealer auto-hits while < 17. Deterministic
    // strategy so the output is the same every run.
    void playOneRound(Deck& deck) {
        std::vector<Card> player, dealer;
        player.push_back(deck.dealCard());
        dealer.push_back(deck.dealCard());
        player.push_back(deck.dealCard());
        dealer.push_back(deck.dealCard());

        show("Player", player);
        show("Dealer", dealer);

        while (score(player) < 17) {
            player.push_back(deck.dealCard());
            show("Player hits → ", player);
        }
        if (score(player) > 21) { std::cout << "Player busts. Dealer wins.\n"; return; }

        while (score(dealer) < 17) {
            dealer.push_back(deck.dealCard());
            show("Dealer hits → ", dealer);
        }
        if (score(dealer) > 21) { std::cout << "Dealer busts. Player wins.\n"; return; }

        int ps { score(player) }, ds { score(dealer) };
        if      (ps > ds) std::cout << "Player wins (" << ps << " vs " << ds << ").\n";
        else if (ds > ps) std::cout << "Dealer wins (" << ds << " vs " << ps << ").\n";
        else              std::cout << "Push (" << ps << " each).\n";
    }
}

void q3_q4() {
    std::cout << "── Q3 / Q4 / Q5: one round of blackjack ──\n";
    std::mt19937 rng { 42 };           // fixed seed → reproducible output
    Cards::Deck deck;
    deck.shuffle(rng);
    Blackjack::playOneRound(deck);
}

int main() {
    q1a();
    q1b();
    q1c();
    std::cout << '\n';
    q2();
    std::cout << '\n';
    q3_q4();
}
