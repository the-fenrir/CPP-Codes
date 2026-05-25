// 23.4 — Association. Doctor and Patient are peers; each tracks the other.
// Neither owns the other; either can be associated with many partners.
#include <functional>
#include <iostream>
#include <string>
#include <vector>

class Patient;   // forward declare — Doctor needs to mention Patient

class Doctor {
    std::string m_name;
    std::vector<std::reference_wrapper<const Patient>> m_patients;
public:
    explicit Doctor(std::string name) : m_name{ std::move(name) } {}
    const std::string& name() const { return m_name; }

    // Bidirectional setup: outside caller pairs them. See pair() below.
    void noteSeen(const Patient& p) { m_patients.emplace_back(p); }

    void listPatients() const;
};

class Patient {
    std::string m_name;
    std::vector<std::reference_wrapper<const Doctor>> m_doctors;

    // Only pair() may wire patients to doctors — keeps the invariant centralised.
    void noteSeenBy(const Doctor& d) { m_doctors.emplace_back(d); }
    friend void pair(Doctor& d, Patient& p);

public:
    explicit Patient(std::string name) : m_name{ std::move(name) } {}
    const std::string& name() const { return m_name; }

    void listDoctors() const {
        std::cout << m_name << " seen by:";
        for (const Doctor& d : m_doctors) std::cout << ' ' << d.name();
        std::cout << '\n';
    }
};

void Doctor::listPatients() const {
    std::cout << "Dr. " << m_name << " has seen:";
    for (const Patient& p : m_patients) std::cout << ' ' << p.name();
    std::cout << '\n';
}

void pair(Doctor& d, Patient& p) {
    d.noteSeen(p);
    p.noteSeenBy(d);          // both sides updated atomically — keep them in sync
}

int main() {
    Doctor  house{ "House" };
    Doctor  cuddy{ "Cuddy" };
    Patient alice{ "Alice" };
    Patient bob  { "Bob"   };

    pair(house, alice);
    pair(house, bob);
    pair(cuddy, alice);

    house.listPatients();
    cuddy.listPatients();
    alice.listDoctors();
    bob.listDoctors();
}
