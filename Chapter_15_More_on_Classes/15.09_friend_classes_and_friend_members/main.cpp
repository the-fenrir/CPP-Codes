// 15.9 — friend class with access to another class's privates.
#include <iostream>

class Vault {
    int m_balance{ 0 };
public:
    void deposit(int amount) { m_balance += amount; }

    friend class Auditor;   // entire Auditor class can read m_balance.
};

class Auditor {
public:
    void inspect(const Vault& v) const {
        // OK only because of the friend declaration in Vault.
        std::cout << "Auditor: vault balance is " << v.m_balance << '\n';
    }
};

int main() {
    Vault v;
    v.deposit(100);
    v.deposit(50);

    Auditor a;
    a.inspect(v);
}
