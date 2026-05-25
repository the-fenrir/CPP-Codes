// 23.1 — four relationships, side by side. Same English-y idea ("X relates to Y"),
// four different storage choices. The storage IS the relationship.
#include <iostream>
#include <string>

// ── Composition: Engine is part of Car. Born with it, dies with it. ──
struct Engine { int horsepower{ 0 }; };
struct Car {
    Engine engine;                 // by value: lifetime tied to Car
    std::string name;
};

// ── Aggregation: Department uses Teachers that already exist elsewhere. ──
struct Teacher { std::string name; };
struct Department {
    const Teacher* head;           // by pointer: Department does NOT own *head
};

// ── Association: Doctor knows Patient (and vice versa, typically). ──
struct Patient { std::string name; };
struct Doctor {
    const Patient* patient;        // also a pointer, but lifetimes are peers
};

// ── Dependency: Point uses ostream once, doesn't store it. ──
struct Point {
    int x, y;
    void print(std::ostream& out) const { out << '(' << x << ',' << y << ")\n"; }
    //                       └─ passed in, used, forgotten
};

int main() {
    Engine e{ 200 };
    Car c{ Engine{ 150 }, "Civic" };           // composition: c owns its engine
    std::cout << c.name << " hp=" << c.engine.horsepower << '\n';

    Teacher t{ "Bob" };
    Department d{ &t };                        // aggregation: t lives outside d
    std::cout << "Head of dept: " << d.head->name << '\n';

    Patient p{ "Alice" };
    Doctor doc{ &p };                          // association
    std::cout << "Doc treats: " << doc.patient->name << '\n';

    Point pt{ 3, 4 };
    pt.print(std::cout);                       // dependency: ostream just passes through

    (void)e;
}
