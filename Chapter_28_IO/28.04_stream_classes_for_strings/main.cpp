// 28.4 — sstream: parse, format, and convert without leaving operator<</>>.
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    // ── numbers -> string with formatting (ostringstream) ─────────────
    {
        std::ostringstream os{};
        os << std::fixed << std::setprecision(2)
           << "pi=" << 3.14159 << " e=" << 2.71828;
        std::cout << "[oss]      " << os.str() << '\n';
    }

    // ── string -> numbers (istringstream) ─────────────────────────────
    {
        std::istringstream is{ "42 3.14 hello" };
        int    n{};
        double d{};
        std::string w{};
        is >> n >> d >> w;
        std::cout << "[iss]      n=" << n << " d=" << d << " w=" << w << '\n';
    }

    // ── tokenize a line on whitespace ─────────────────────────────────
    {
        std::istringstream is{ "the quick brown fox" };
        std::string tok{};
        std::cout << "[tokens]   ";
        while (is >> tok) std::cout << '[' << tok << ']';
        std::cout << '\n';
    }

    // ── stringstream round-trip (both directions on one buffer) ───────
    {
        std::stringstream ss{};
        ss << 100 << ' ' << 2.5;
        int    n{};
        double d{};
        ss >> n >> d;
        std::cout << "[round]    n=" << n << " d=" << d << '\n';
    }

    // ── reuse: str("") + clear() ──────────────────────────────────────
    // Without clear(), the failbit set by the previous EOF extraction
    // would block all further reads from the new content.
    {
        std::stringstream ss{};
        ss << 1 << ' ' << 2;
        int a{}, b{}, c{}, d{};
        ss >> a >> b;
        ss >> c;             // fails — past end
        std::cout << "[reuse-1]  fail()=" << ss.fail() << '\n';

        ss.str("30 40");     // new content
        ss.clear();          // <- critical
        ss >> c >> d;
        std::cout << "[reuse-2]  a=" << a << " b=" << b
                  << " c=" << c << " d=" << d << '\n';
    }
}
