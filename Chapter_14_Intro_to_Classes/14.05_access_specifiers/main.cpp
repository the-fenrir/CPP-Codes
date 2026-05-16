// 14.5 — public interface, private state, per-class (not per-object) access.
#include <iostream>

class Wallet {
    int m_cents{ 0 };  // private by default (class)
public:
    void deposit(int c) { m_cents += c; }
    int  balance() const { return m_cents; }

    // Per-class access: this Wallet can poke OTHER Wallets' privates.
    void transferTo(Wallet& other, int c) {
        m_cents       -= c;
        other.m_cents += c;   // legal — same class, even though `other` is a different object.
    }
};

int main() {
    Wallet a, b;
    a.deposit(100);
    a.transferTo(b, 30);
    std::cout << "a=" << a.balance() << " b=" << b.balance() << '\n';
}
