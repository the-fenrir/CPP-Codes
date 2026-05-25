// Chapter 21 quiz solutions.
//   Q1: discussion — see NOTES.md
//   Q2: Average — operator+= (member), operator<< (non-member)
//   Q3: IntArray — deep copy, self-assignment-safe
//   Q4: FixedPoint2 — int16/int8 storage, double round-trip, ==, +, unary -
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>

// ── Q2: Average ──────────────────────────────────────────────────────
//
// Design notes:
//  • Track total + count. The average is computed on demand (avoids cumulative
//    floating-point drift, and lets us answer `m_count == 0` cleanly with 0).
//  • `operator+=` is a member returning `Average&` — required for the test's
//    `(avg += 6) += 10;` chained re-mutation pattern.
//  • `operator<<` is a non-member, friend only so it can read both members
//    cheaply. Could also be implemented through public accessors with no friend.
class Average {
    std::int64_t m_total{ 0 };
    std::int32_t m_count{ 0 };
public:
    Average() = default;

    Average& operator+=(int n) {
        m_total += n;
        ++m_count;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Average& a) {
        if (a.m_count == 0) return out << 0;
        return out << static_cast<double>(a.m_total) / a.m_count;
    }
};

// ── Q3: IntArray ─────────────────────────────────────────────────────
//
// Design notes:
//  • Owns a raw `int*`. Rule-of-three applies: copy ctor, copy assignment,
//    destructor — all explicit and all do deep work.
//  • Copy assignment guards self-assignment, then *frees first* before
//    allocating, so the stale buffer doesn't leak.
//  • Two operator[] overloads (mutable + const). Pre-condition asserted.
//  • Move ctor/assignment would be useful here but are not required by the
//    test program — kept out for clarity. Real production code would have them.
class IntArray {
    int*        m_data{ nullptr };
    std::size_t m_len{ 0 };
public:
    explicit IntArray(std::size_t len) : m_data{ new int[len]{} }, m_len{ len } {
        assert(len > 0);
    }

    IntArray(const IntArray& o) : m_data{ new int[o.m_len]{} }, m_len{ o.m_len } {
        for (std::size_t i = 0; i < m_len; ++i) m_data[i] = o.m_data[i];
    }

    IntArray& operator=(const IntArray& o) {
        if (this == &o) return *this;
        delete[] m_data;
        m_len  = o.m_len;
        m_data = new int[m_len]{};
        for (std::size_t i = 0; i < m_len; ++i) m_data[i] = o.m_data[i];
        return *this;
    }

    ~IntArray() { delete[] m_data; }

    int&       operator[](std::size_t i)       { assert(i < m_len); return m_data[i]; }
    const int& operator[](std::size_t i) const { assert(i < m_len); return m_data[i]; }

    std::size_t size() const { return m_len; }

    friend std::ostream& operator<<(std::ostream& out, const IntArray& a) {
        for (std::size_t i = 0; i < a.m_len; ++i) {
            if (i) out << ' ';
            out << a.m_data[i];
        }
        return out << '\n';
    }
};

IntArray fillArray() {
    IntArray a{ 5 };
    a[0] = 5; a[1] = 8; a[2] = 2; a[3] = 3; a[4] = 6;
    return a;
}

// ── Q4: FixedPoint2 ──────────────────────────────────────────────────
//
// Design notes:
//  • Two integer members: base (int16) and decimal (int8). Both carry sign
//    independently; the constructor normalises so they agree (so we don't have
//    ambiguous representations like base=+1, decimal=-50 meaning "+0.50").
//  • Decimal overflow (`{1, 104}` → 2.04) is folded into base in the ctor.
//  • Double constructor rounds to 2 decimals and reuses the (int16,int8) ctor.
//    Rounding uses std::round on (d * 100) to land on the nearest cent.
//  • Arithmetic (+) is implemented by round-tripping through `double` — simple,
//    correct, and the precision loss is invisible at 2 decimal places.
class FixedPoint2 {
    std::int16_t m_base{ 0 };
    std::int8_t  m_dec{ 0 };

    void normalise() {
        // Fold decimal overflow into base. With int8 dec this only triggers
        // if the caller passes something out of [-99..99] (which int8 can't
        // even hold above 127, but worth being defensive for completeness).
        if (m_dec >= 100 || m_dec <= -100) {
            m_base = static_cast<std::int16_t>(m_base + m_dec / 100);
            m_dec  = static_cast<std::int8_t>(m_dec % 100);
        }
        // Make signs agree. Two ways the caller can disagree:
        //   {-2,  5} meant -2.05  →  flip m_dec negative
        //   { 2, -5} meant -2.05  →  flip m_base negative
        if (m_base < 0 && m_dec > 0) m_dec  = static_cast<std::int8_t> (-m_dec);
        if (m_base > 0 && m_dec < 0) m_base = static_cast<std::int16_t>(-m_base);
    }

public:
    FixedPoint2(std::int16_t base, std::int8_t decimal)
        : m_base{ base }, m_dec{ decimal }
    {
        normalise();
    }

    FixedPoint2(double d) {
        // Round to nearest cent. Sign of d carries through std::round.
        const double cents = std::round(d * 100.0);
        m_base = static_cast<std::int16_t>(cents / 100);
        m_dec  = static_cast<std::int8_t>(static_cast<long long>(cents) % 100);
        // Signs already agree because we derived both from the same number.
    }

    explicit operator double() const { return m_base + m_dec / 100.0; }

    friend bool operator==(const FixedPoint2& a, const FixedPoint2& b) {
        return a.m_base == b.m_base && a.m_dec == b.m_dec;
    }

    FixedPoint2 operator-() const {
        // Negate both members; normalise() not needed since signs stay aligned.
        return FixedPoint2{ static_cast<std::int16_t>(-m_base),
                            static_cast<std::int8_t>(-m_dec) };
    }

    friend FixedPoint2 operator+(const FixedPoint2& a, const FixedPoint2& b) {
        return FixedPoint2{ static_cast<double>(a) + static_cast<double>(b) };
    }

    friend std::ostream& operator<<(std::ostream& out, const FixedPoint2& f) {
        return out << static_cast<double>(f);
    }
    friend std::istream& operator>>(std::istream& in, FixedPoint2& f) {
        double d{};
        in >> d;
        f = FixedPoint2{ d };
        return in;
    }
};

int main() {
    std::cout << "── Q2: Average ──\n";
    Average avg{};
    std::cout << avg << '\n';        // 0
    avg += 4;
    std::cout << avg << '\n';        // 4
    avg += 8;
    std::cout << avg << '\n';        // 6
    avg += 24;
    std::cout << avg << '\n';        // 12
    avg += -10;
    std::cout << avg << '\n';        // 6.5
    (avg += 6) += 10;
    std::cout << avg << '\n';        // 7
    Average copy{ avg };
    std::cout << copy << '\n';       // 7

    std::cout << "\n── Q3: IntArray ──\n";
    IntArray a{ fillArray() };
    std::cout << a;
    auto b{ a };
    // Self-assignment is part of the Q3 spec — silence the well-meaning warning.
#if defined(__clang__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wself-assign-overloaded"
#elif defined(__GNUC__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wpragmas"
#endif
    a = a;
    b = b;
#if defined(__clang__)
#  pragma clang diagnostic pop
#elif defined(__GNUC__)
#  pragma GCC diagnostic pop
#endif
    std::cout << b;

    std::cout << "\n── Q4: FixedPoint2 ──\n";
    FixedPoint2 fa{ 34, 56 };   std::cout << fa << '\n';   // 34.56
    FixedPoint2 fb{ -2, 5 };    std::cout << fb << '\n';   // -2.05
    FixedPoint2 fc{ 2, -5 };    std::cout << fc << '\n';   // -2.05
    FixedPoint2 fd{ -2, -5 };   std::cout << fd << '\n';   // -2.05
    FixedPoint2 fe{ 0, -5 };    std::cout << fe << '\n';   // -0.05
    FixedPoint2 ff{ 1, 104 };   std::cout << ff << '\n';   // 2.04 (overflow)

    FixedPoint2 fg{ 0.05 };     std::cout << fg << '\n';   // 0.05
    FixedPoint2 fh{ -0.048 };   std::cout << fh << '\n';   // -0.05
    FixedPoint2 fi{ 106.9978 }; std::cout << fi << '\n';   // 107

    std::cout << "0.75 + 1.23 = " << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 }) << '\n'; // 1.98
    std::cout << "negation of 1.98 = " << -(FixedPoint2{ 1.98 }) << '\n';                  // -1.98

    // istream demo via stringstream so the run is non-interactive.
    std::istringstream src{ "5.678" };
    FixedPoint2 fj{ 0.0 };
    src >> fj;
    std::cout << "parsed 5.678 → " << fj << '\n';   // 5.68
}
