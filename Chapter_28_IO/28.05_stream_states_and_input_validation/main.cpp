// 28.5 — stream state bits, the classic failure modes, and recovery.
//
// All "user input" is via std::istringstream so this is reproducible.
// The recovery idioms are identical for std::cin.
#include <charconv>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

static void show(const char* label, const std::istringstream& s) {
    std::cout << label
              << " good=" << s.good()
              << " fail=" << s.fail()
              << " eof="  << s.eof()
              << " bad="  << s.bad() << '\n';
}

int main() {
    // ── (1) clean input: just works ───────────────────────────────────
    {
        std::istringstream in{ "42\n" };
        int n{};
        in >> n;
        std::cout << "[ok]       n=" << n << '\n';
        show("[ok]      ", in);
    }

    // ── (2) bad input ("abc"): failbit set, recover with clear+ignore ─
    {
        std::istringstream in{ "abc\n99\n" };
        int n{};
        in >> n;
        show("[fail-1]  ", in);                   // fail=1

        in.clear();                               // reset bits
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        in >> n;                                  // now reads the 99
        std::cout << "[recover]  n=" << n << '\n';
        show("[fail-2]  ", in);
    }

    // ── (3) partial input ("34abcd"): silent garbage — the real trap ──
    {
        std::istringstream in{ "34abcd\n" };
        int n{};
        in >> n;
        std::cout << "[partial]  n=" << n
                  << " fail=" << in.fail()        // FALSE — looks fine!
                  << " peek=" << static_cast<char>(in.peek()) << '\n';
        // Detect: anything other than '\n'/whitespace next means garbage.
    }

    // ── (4) the modern recipe: read line, parse with from_chars ───────
    {
        std::istringstream in{ "34abcd\n42\n" };
        std::string line{};
        while (std::getline(in, line)) {
            int n{};
            auto [ptr, ec] = std::from_chars(line.data(),
                                             line.data() + line.size(), n);
            const bool whole = (ec == std::errc{}) &&
                               (ptr == line.data() + line.size());
            std::cout << "[parse]    line=\"" << line
                      << "\" parsed=" << n
                      << " whole=" << whole << '\n';
        }
    }
}
