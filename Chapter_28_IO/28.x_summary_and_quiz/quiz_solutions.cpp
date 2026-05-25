// Chapter 28 end-to-end demo (no official quiz on learncpp).
//
// Walks one piece of data through every concept in the chapter:
//   • format with ostringstream  (28.3, 28.4)
//   • validate with from_chars   (28.5)
//   • write records to a file    (28.6)
//   • random-access read         (28.7)
//
// Runs non-interactively; cleans up its temp file.
#include <charconv>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>

namespace fs = std::filesystem;

// 28.5 idiom: parse an integer from a string, reject anything partial.
static std::optional<int> parse_int(std::string_view s) {
    int n{};
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), n);
    if (ec != std::errc{} || ptr != s.data() + s.size()) return {};
    return n;
}

// Fixed-width record for binary random access (28.7).
struct Record {
    std::int32_t id;
    char         name[16];
    double       balance;
};
static_assert(sizeof(Record) == 32 || sizeof(Record) == 24
              || sizeof(Record) == 28, "alignment varies but must be fixed");

int main() {
    // ── 1. format a "human" line with ostringstream + manipulators ────
    std::ostringstream os{};
    os << std::left  << std::setw(8) << "id"
       << std::left  << std::setw(16) << "name"
       << std::right << std::fixed << std::setprecision(2) << "balance";
    std::cout << "[header]   " << os.str() << '\n';

    // ── 2. validate some inputs (28.5) ────────────────────────────────
    for (std::string_view s : { "42", "34abcd", "", "-7" }) {
        auto v = parse_int(s);
        std::cout << "[parse]    \"" << s << "\" -> "
                  << (v ? std::to_string(*v) : std::string{"<invalid>"}) << '\n';
    }

    // ── 3. write fixed-size records, binary mode (28.6 + 28.7) ────────
    const fs::path path = fs::temp_directory_path() / "cpp28_x_demo.bin";

    Record rs[] = {
        Record{ 1, "", 100.25 },
        Record{ 2, "", 250.00 },
        Record{ 3, "", -17.50 },
    };
    std::strncpy(rs[0].name, "alice",   sizeof(rs[0].name) - 1);
    std::strncpy(rs[1].name, "bob",     sizeof(rs[1].name) - 1);
    std::strncpy(rs[2].name, "charlie", sizeof(rs[2].name) - 1);

    {
        std::ofstream out{ path, std::ios::binary | std::ios::trunc };
        if (!out) { std::cerr << "open failed\n"; return 1; }
        out.write(reinterpret_cast<const char*>(rs), sizeof(rs));
    }

    // ── 4. report size + read record #1 by seeking (28.7) ─────────────
    {
        std::ifstream in{ path, std::ios::binary };
        in.seekg(0, std::ios::end);
        const auto sz = in.tellg();
        std::cout << "[file]     " << sz << " bytes\n";

        in.seekg(sizeof(Record) * 1, std::ios::beg);
        Record r{};
        in.read(reinterpret_cast<char*>(&r), sizeof(r));

        std::cout << "[seek-r1]  "
                  << std::left  << std::setw(8) << r.id
                  << std::left  << std::setw(16) << r.name
                  << std::right << std::fixed << std::setprecision(2) << r.balance
                  << '\n';
    }

    // ── 5. cleanup ────────────────────────────────────────────────────
    std::error_code ec{};
    fs::remove(path, ec);
}
