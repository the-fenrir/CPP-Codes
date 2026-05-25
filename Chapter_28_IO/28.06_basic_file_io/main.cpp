// 28.6 — basic file I/O: write, read, append, RAII close.
//
// We use a temp directory so we don't litter the repo. The demo file
// is deleted at the end.
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int main() {
    namespace fs = std::filesystem;
    const fs::path path = fs::temp_directory_path() / "cpp28_06_demo.txt";

    // ── write (truncating) ────────────────────────────────────────────
    {
        std::ofstream out{ path };
        if (!out) {
            std::cerr << "open for write failed: " << path << '\n';
            return 1;
        }
        out << "line one\n";
        out << "line two has " << 3 << " tokens\n";
        out << "line three\n";
        // out closes here via RAII.
    }
    std::cout << "[write]    wrote " << path << '\n';

    // ── read line-by-line ─────────────────────────────────────────────
    {
        std::ifstream in{ path };
        if (!in) { std::cerr << "open for read failed\n"; return 1; }
        std::string line{};
        int n = 0;
        while (std::getline(in, line)) {
            std::cout << "[line " << ++n << "]   " << line << '\n';
        }
    }

    // ── read token-by-token (>>) ──────────────────────────────────────
    {
        std::ifstream in{ path };
        std::string tok{};
        std::cout << "[tokens]   ";
        while (in >> tok) std::cout << '[' << tok << ']';
        std::cout << '\n';
    }

    // ── append ────────────────────────────────────────────────────────
    {
        std::ofstream out{ path, std::ios::app };   // <-- key flag
        out << "appended line four\n";
    }

    // ── verify the append landed ──────────────────────────────────────
    {
        std::ifstream in{ path };
        std::string line{};
        while (std::getline(in, line)) {
            std::cout << "[after]    " << line << '\n';
        }
    }

    std::error_code ec{};
    fs::remove(path, ec);   // best-effort cleanup
}
