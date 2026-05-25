// 22.3 — Side-by-side copy ctor / move ctor / copy assign / move assign.
//
// Watch the trace prints — that's the whole point of this lesson.
#include <iostream>
#include <utility>

template <typename T>
class Auto_ptr3 {
    T* m_ptr{};
public:
    Auto_ptr3(T* ptr = nullptr) : m_ptr{ ptr } {}
    ~Auto_ptr3() { delete m_ptr; }

    // Copy: deep clone.
    Auto_ptr3(const Auto_ptr3& a) {
        std::cout << "  copy ctor\n";
        m_ptr = a.m_ptr ? new T{ *a.m_ptr } : nullptr;
    }
    Auto_ptr3& operator=(const Auto_ptr3& a) {
        std::cout << "  copy assign\n";
        if (&a == this) return *this;
        delete m_ptr;
        m_ptr = a.m_ptr ? new T{ *a.m_ptr } : nullptr;
        return *this;
    }

    // Move: steal pointer, null the source.
    Auto_ptr3(Auto_ptr3&& a) noexcept : m_ptr{ a.m_ptr } {
        std::cout << "  move ctor\n";
        a.m_ptr = nullptr;
    }
    Auto_ptr3& operator=(Auto_ptr3&& a) noexcept {
        std::cout << "  move assign\n";
        if (&a == this) return *this;
        delete m_ptr;
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
        return *this;
    }

    T& operator*()  const { return *m_ptr; }
    T* operator->() const { return  m_ptr; }
};

struct Resource {
    Resource()  { std::cout << "  Resource ctor\n"; }
    ~Resource() { std::cout << "  Resource dtor\n"; }
};

Auto_ptr3<Resource> makeResource() {
    Auto_ptr3<Resource> r{ new Resource{} };
    return r;                       // typically NRVO'd; otherwise moves
}

int main() {
    std::cout << "── construct from rvalue (returned by value) ──\n";
    Auto_ptr3<Resource> a{ makeResource() };

    std::cout << "\n── construct from lvalue (copy) ──\n";
    Auto_ptr3<Resource> b{ a };

    std::cout << "\n── assign from rvalue (move) ──\n";
    b = makeResource();

    std::cout << "\n── assign from lvalue (copy) ──\n";
    Auto_ptr3<Resource> c;
    c = b;

    std::cout << "\n── std::move forces the move overload on an lvalue ──\n";
    Auto_ptr3<Resource> d;
    d = std::move(c);

    std::cout << "\n── scope ends, dtors run ──\n";
}
