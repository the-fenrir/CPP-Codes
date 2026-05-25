// 28.7 — random file I/O with seekg/seekp/tellg + in-place update.
//
// Binary mode + fixed-size records is the model that makes random
// access actually work. Text mode + variable-length lines does NOT.
#include <array>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

struct Record {
    std::int32_t id;
    char         name[16];   // fixed-width so every record is 20 bytes
};
static_assert(sizeof(Record) == 20, "padding will break random access");

static Record make(std::int32_t id, const char* n) {
    Record r{};
    r.id = id;
    std::strncpy(r.name, n, sizeof(r.name) - 1);
    return r;
}

int main() {
    namespace fs = std::filesystem;
    const fs::path path = fs::temp_directory_path() / "cpp28_07_demo.bin";

    // ── write three records, binary mode ──────────────────────────────
    {
        std::ofstream out{ path, std::ios::binary | std::ios::trunc };
        if (!out) { std::cerr << "open for write failed\n"; return 1; }
        const Record rs[] = { make(1, "alice"), make(2, "bob"), make(3, "carol") };
        out.write(reinterpret_cast<const char*>(rs), sizeof(rs));
    }

    // ── (a) file size via seek/tell ───────────────────────────────────
    {
        std::ifstream in{ path, std::ios::binary };
        in.seekg(0, std::ios::end);
        const auto sz = in.tellg();
        std::cout << "[size]     " << sz << " bytes ("
                  << (sz / static_cast<std::streamoff>(sizeof(Record)))
                  << " records)\n";
    }

    // ── (b) seek to record 1 (the second one) and read it ─────────────
    {
        std::ifstream in{ path, std::ios::binary };
        in.seekg(sizeof(Record) * 1, std::ios::beg);
        Record r{};
        in.read(reinterpret_cast<char*>(&r), sizeof(r));
        std::cout << "[seek-r1]  id=" << r.id << " name=" << r.name << '\n';
    }

    // ── (c) read+write fstream: rewrite record 2 in place ─────────────
    {
        std::fstream io{ path, std::ios::binary | std::ios::in | std::ios::out };
        io.seekp(sizeof(Record) * 2, std::ios::beg);
        const Record updated = make(99, "carol2");
        io.write(reinterpret_cast<const char*>(&updated), sizeof(updated));
        // No need to seek before closing — destructor flushes.
    }

    // ── verify ────────────────────────────────────────────────────────
    {
        std::ifstream in{ path, std::ios::binary };
        Record r{};
        int i = 0;
        while (in.read(reinterpret_cast<char*>(&r), sizeof(r))) {
            std::cout << "[after " << i++ << "]  id=" << r.id
                      << " name=" << r.name << '\n';
        }
    }

    std::error_code ec{};
    fs::remove(path, ec);
}
