// Chapter 19 quiz solutions.
//   Q1: leak / double-delete / wrong-delete / lost-address — diagnosed.
//   Q2: sorted dynamic string array with new[] / delete[].
//   Q3: IntBuffer — RAII wrapper around new int[].
//   Q4: 4x5 grid stored as a flat new int[20], indexed by row*cols + col.
//   Q5: void pointer vs null pointer — discussion in comments.
//
// Compiles clean with -Wall -Wextra -Wpedantic; valgrind-clean
// (every `new`/`new[]` is matched with one `delete`/`delete[]`).
#include <algorithm>
#include <iostream>
#include <string>

// ── Q1: bug-spotting fixes ──────────────────────────────────────────────
//
// (a) Early return leaks p. Fix: delete before return, or use std::unique_ptr.
// (b) Double-delete of the same address through aliased pointer.
//     Fix: only one pointer owns; the other should be a non-owning observer
//     (or just use std::unique_ptr / std::shared_ptr to encode ownership).
// (c) Allocated with new[], freed with delete (scalar). UB.
//     Fix: delete[] p;
// (d) The first allocation's address is overwritten by the second `new`.
//     Original block is leaked. Fix: delete p; before reassigning, or
//     use std::unique_ptr which calls reset() correctly.
//
// Worked correct versions:
namespace q1 {
    void a() {
        int* p = new int{ 1 };
        if (*p < 0) { delete p; return; }   // free before early return
        delete p;
    }
    void b() {
        int* p = new int{ 1 };
        int* q = p;                          // q is a *view*, not an owner
        (void)q;
        delete p;                            // exactly one delete
    }
    void c() {
        int* p = new int[10]{};
        delete[] p;                          // match new[] with delete[]
    }
    void d() {
        int* p = new int{ 1 };
        delete p;                            // free old before reassigning
        p = new int{ 2 };
        delete p;
    }
}

// ── Q3: IntBuffer — RAII owner ──────────────────────────────────────────
//
// Constructor allocates; destructor frees. Copy ops deleted because the
// compiler-generated copy would memcpy the pointer and produce two owners
// — the Rule of Three (ch. 22 covers writing them correctly).
class IntBuffer {
    int*        m_data;
    std::size_t m_size;
public:
    IntBuffer(std::size_t n)
        : m_data{ new int[n]{} }, m_size{ n }
    {
        std::cout << "  IntBuffer(" << m_size << ") ctor\n";
    }
    ~IntBuffer() {
        std::cout << "  IntBuffer(" << m_size << ") dtor\n";
        delete[] m_data;
    }
    IntBuffer(const IntBuffer&)            = delete;
    IntBuffer& operator=(const IntBuffer&) = delete;

    std::size_t size() const             { return m_size; }
    int&  operator[](std::size_t i)       { return m_data[i]; }
    int   operator[](std::size_t i) const { return m_data[i]; }
};

void q3_stack_scope() {
    std::cout << "q3 stack scope: enter\n";
    IntBuffer buf{ 4 };
    for (std::size_t i = 0; i < buf.size(); ++i) buf[i] = static_cast<int>(i * i);
    std::cout << "  buf =";
    for (std::size_t i = 0; i < buf.size(); ++i) std::cout << ' ' << buf[i];
    std::cout << '\n';
    std::cout << "q3 stack scope: leave\n";
}   // ← buf's destructor runs here, automatically

int main() {
    // ── Q1: run the fixed versions ──────────────────────────────────────
    std::cout << "── Q1: fixed versions run without leaks ──\n";
    q1::a(); q1::b(); q1::c(); q1::d();
    std::cout << "  (no output by design; valgrind reports zero leaks)\n";

    // ── Q2: sorted dynamic name array ───────────────────────────────────
    std::cout << "\n── Q2: dynamic sorted name array ──\n";
    {
        const std::size_t n{ 5 };
        std::string* names{ new std::string[n]{
            "delta", "alpha", "echo", "bravo", "charlie"
        } };

        std::sort(names, names + n);
        for (std::size_t i = 0; i < n; ++i) std::cout << "  " << names[i] << '\n';

        delete[] names;     // new[] ↔ delete[]
        names = nullptr;

        // Modern one-liner equivalent (no new/delete):
        //   std::vector<std::string> v{ "delta","alpha","echo","bravo","charlie" };
        //   std::sort(v.begin(), v.end());
        //   for (const auto& s : v) std::cout << s << '\n';
    }

    // ── Q3: RAII IntBuffer ──────────────────────────────────────────────
    std::cout << "\n── Q3: IntBuffer ──\n";
    q3_stack_scope();                       // stack: dtor on scope exit

    std::cout << "q3 heap: allocate\n";
    IntBuffer* hb{ new IntBuffer{ 3 } };    // heap: dtor on delete
    (*hb)[0] = 7; (*hb)[1] = 8; (*hb)[2] = 9;
    std::cout << "  heap buf =";
    for (std::size_t i = 0; i < hb->size(); ++i) std::cout << ' ' << (*hb)[i];
    std::cout << '\n';
    delete hb;
    hb = nullptr;

    // ── Q4: flat 4x5 grid ───────────────────────────────────────────────
    std::cout << "\n── Q4: flat 4x5 grid ──\n";
    {
        constexpr std::size_t rows{ 4 };
        constexpr std::size_t cols{ 5 };
        int* grid{ new int[rows * cols]{} };

        auto at = [&](std::size_t r, std::size_t c) -> int& {
            return grid[r * cols + c];
        };

        for (std::size_t r = 0; r < rows; ++r)
            for (std::size_t c = 0; c < cols; ++c)
                at(r, c) = static_cast<int>(r * 10 + c);

        for (std::size_t r = 0; r < rows; ++r) {
            for (std::size_t c = 0; c < cols; ++c) std::cout << at(r, c) << '\t';
            std::cout << '\n';
        }

        delete[] grid;                       // one new[], one delete[]
        grid = nullptr;
    }

    // ── Q5: void pointer vs null pointer ────────────────────────────────
    //
    // A *void pointer* is a pointer whose TYPE has been erased — it stores
    // an address but the compiler doesn't know what kind of object lives
    // there, so you can't dereference it or do pointer arithmetic without
    // casting back to the original type first.
    //
    // A *null pointer* is a pointer whose VALUE is "no address" (nullptr).
    // It says nothing about the pointer's type.
    //
    // The two are orthogonal: a pointer can be one, the other, both, or
    // neither. `void* p = nullptr;` is a null void pointer; `int* q = &x;`
    // is a non-null int pointer. "Type" vs "value" — different axes.
    std::cout << "\n── Q5: see comment in source ──\n";
}
