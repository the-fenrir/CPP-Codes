// 26.6 — partial specialization for pointers, two ownership variants.
#include <iostream>
#include <memory>

// ── View variant ────────────────────────────────────────────────────
// Primary: value semantics.
template <typename T>
class Storage {
    T m_value{};
public:
    explicit Storage(const T& value) : m_value{ value } {}
    void print() const { std::cout << m_value << '\n'; }
};

// Partial specialization for raw pointers — *view* semantics, no ownership.
// Caller must keep the pointee alive for the lifetime of this Storage.
template <typename T>
class Storage<T*> {
    T* m_value{ nullptr };
public:
    explicit Storage(T* value) : m_value{ value } {}
    void print() const {
        if (m_value) std::cout << *m_value << '\n';
        else         std::cout << "(null)\n";
    }
};

// ── Owning variant ──────────────────────────────────────────────────
// A second template name, this time the pointer specialization deep-copies.
template <typename T>
class StorageOwning {
    T m_value{};
public:
    explicit StorageOwning(const T& value) : m_value{ value } {}
    void print() const { std::cout << m_value << '\n'; }
};

template <typename T>
class StorageOwning<T*> {
    std::unique_ptr<T> m_value;
public:
    explicit StorageOwning(T* value)
        : m_value{ value ? std::make_unique<T>(*value) : nullptr } {}
    void print() const {
        if (m_value) std::cout << *m_value << '\n';
        else         std::cout << "(null)\n";
    }
};

int main() {
    int x{ 42 };

    Storage<int>  byValue{ x };
    Storage<int*> byView{ &x };       // shares the int with main()
    byValue.print();
    byView.print();
    x = 100;
    byValue.print();   // unchanged: it owns a copy
    byView.print();    // changed: it was a view

    std::cout << "─── owning specialization ───\n";
    int y{ 7 };
    StorageOwning<int*> owned{ &y };
    y = 999;
    owned.print();     // 7 — deep copy is decoupled from y
}
