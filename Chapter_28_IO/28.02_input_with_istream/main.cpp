// 28.2 — istream extraction, get/getline, peek/unget, the \n bug.
//
// We drive all of this against std::istringstream so `make` runs it
// non-interactively. The API is identical to std::cin — istringstream
// IS an istream — so anything that works here works on stdin.
#include <iostream>
#include <sstream>
#include <string>

int main() {
    // ── operator>> ─────────────────────────────────────────────────────
    // Skips leading whitespace, stops at next whitespace, leaves rest behind.
    {
        std::istringstream in{ "   42 hello\n" };
        int n{}; std::string word{};
        in >> n >> word;
        std::cout << "[>>]      n=" << n << " word=" << word << '\n';
    }

    // ── the classic >> + getline bug, and the fix ─────────────────────
    {
        std::istringstream in{ "42\nthe rest of the line\n" };
        int n{}; std::string line{};
        in >> n;
        std::getline(in, line);   // BUG: reads the empty tail after 42, not "the rest..."
        std::cout << "[bug]     n=" << n << " line=\"" << line << "\"\n";
    }
    {
        std::istringstream in{ "42\nthe rest of the line\n" };
        int n{}; std::string line{};
        in >> n;
        in >> std::ws;            // FIX: discard the trailing whitespace incl. '\n'
        std::getline(in, line);
        std::cout << "[fix]     n=" << n << " line=\"" << line << "\"\n";
    }

    // ── get vs getline (delimiter handling) ───────────────────────────
    {
        std::istringstream in{ "line one\nline two\n" };
        std::string a{}, b{};
        std::getline(in, a);      // consumes '\n'
        std::getline(in, b);
        std::cout << "[getline] a=\"" << a << "\" b=\"" << b << "\"\n";
    }

    // ── peek + unget ──────────────────────────────────────────────────
    {
        std::istringstream in{ "abc" };
        int p = in.peek();        // returns int (room for EOF)
        char c1{}; in.get(c1);
        in.unget();               // push c1 back
        char c2{}; in.get(c2);
        std::cout << "[peek]    peek=" << static_cast<char>(p)
                  << " c1=" << c1 << " c2(after unget)=" << c2 << '\n';
    }

    // ── ignore: skip to end of line ───────────────────────────────────
    {
        std::istringstream in{ "junk to throw away\nkeep this\n" };
        in.ignore(1000, '\n');
        std::string keep{}; std::getline(in, keep);
        std::cout << "[ignore]  keep=\"" << keep << "\"\n";
    }
}
