// Chapter 25 quiz solutions.
//   Q1a–Q1f: six tiny polymorphism bugs, each in its own namespace, fixed.
//   Q2a–Q2c: Shape / Circle / Triangle with polymorphic operator<<,
//            vector<Shape*>, getLargestRadius via dynamic_cast.
//   Q2d:     same problem, but std::vector<std::unique_ptr<Shape>>.
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

// ── Q1a: was `Base b = d;` (slicing). Fix: bind by reference. ──────────
namespace q1a {
    class Base {
    public:
        virtual const char* getName() const { return "Base"; }
        virtual ~Base() = default;
    };
    class Derived : public Base {
    public:
        const char* getName() const override { return "Derived"; }
    };
    void run() {
        Derived d{};
        const Base& b{ d };                 // reference, no slicing
        std::cout << "Q1a: " << b.getName() << '\n';
    }
}

// ── Q1b: const mismatch silently turned override into overload. ────────
namespace q1b {
    class Base {
    public:
        virtual const char* getName() const { return "Base"; } // add const
        virtual ~Base() = default;
    };
    class Derived : public Base {
    public:
        const char* getName() const override { return "Derived"; }
    };
    void run() {
        Derived d{};
        const Base& b{ d };
        std::cout << "Q1b: " << b.getName() << '\n';
    }
}

// ── Q1c: was `Base b; b = d;` (assignment slices). Fix: reference. ─────
namespace q1c {
    class Base {
    public:
        virtual const char* getName() const { return "Base"; }
        virtual ~Base() = default;
    };
    class Derived : public Base {
    public:
        const char* getName() const override { return "Derived"; }
    };
    void run() {
        Derived d{};
        const Base& b{ d };                 // no assignment, no slicing
        std::cout << "Q1c: " << b.getName() << '\n';
    }
}

// ── Q1d: was `class Base final`. Remove `final` so Derived can inherit. ─
namespace q1d {
    class Base {                             // was: class Base final
    public:
        virtual const char* getName() const { return "Base"; }
        virtual ~Base() = default;
    };
    class Derived : public Base {
    public:
        const char* getName() const override { return "Derived"; }
    };
    void run() {
        Derived d{};
        const Base& b{ d };
        std::cout << "Q1d: " << b.getName() << '\n';
    }
}

// ── Q1e: had `override = 0 { … }` — pure virtual with inline body is ill-formed.
//        Pick one: a regular override OR a pure virtual declaration. Here: regular override.
namespace q1e {
    class Base {
    public:
        virtual const char* getName() const { return "Base"; }
        virtual ~Base() = default;
    };
    class Derived : public Base {
    public:
        const char* getName() const override { return "Derived"; } // not pure
    };
    void run() {
        Derived d{};
        const Base& b{ d };
        std::cout << "Q1e: " << b.getName() << '\n';
    }
}

// ── Q1f: non-virtual ~Base → ~Derived skipped on `delete p`. Make it virtual.
namespace q1f {
    class Base {
    public:
        virtual const char* getName() const { return "Base"; }
        virtual ~Base() = default;           // was: ~Base() {} (non-virtual)
    };
    class Derived : public Base {
    public:
        const char* getName() const override { return "Derived"; }
    };
    void run() {
        Base* p = new Derived{};
        std::cout << "Q1f: " << p->getName() << '\n';
        delete p;                            // ~Derived then ~Base
    }
}

// ── Q2: Shape / Circle / Triangle ─────────────────────────────────────
//
// Design notes:
//  • `Shape` is an interface: pure virtual print(), virtual dtor, no data.
//  • One free operator<<(ostream&, const Shape&) for the whole hierarchy;
//    it forwards to the virtual print(), so dispatch is correct (25.11).
//  • `Circle::getRadius()` exists so getLargestRadius can read it after a
//    successful dynamic_cast. Could be `const Circle::m_radius` access via
//    a public accessor (what we do) or via friendship — accessor is cleaner.
//  • getLargestRadius returns int (radii are int per the spec). Returns 0
//    if there are no Circles, which is a reasonable sentinel here.

class Point {
    int m_x{};
    int m_y{};
public:
    Point(int x, int y) : m_x{ x }, m_y{ y } {}
    friend std::ostream& operator<<(std::ostream& out, const Point& p) {
        return out << "Point(" << p.m_x << ", " << p.m_y << ')';
    }
};

class Shape {
public:
    virtual std::ostream& print(std::ostream& out) const = 0;
    virtual ~Shape() = default;
};

std::ostream& operator<<(std::ostream& out, const Shape& s) {
    return s.print(out);
}

class Triangle : public Shape {
    Point m_a, m_b, m_c;
public:
    Triangle(const Point& a, const Point& b, const Point& c)
        : m_a{ a }, m_b{ b }, m_c{ c } {}
    std::ostream& print(std::ostream& out) const override {
        return out << "Triangle(" << m_a << ", " << m_b << ", " << m_c << ')';
    }
};

class Circle : public Shape {
    Point m_center;
    int   m_radius;
public:
    Circle(const Point& center, int radius)
        : m_center{ center }, m_radius{ radius } {}
    int getRadius() const { return m_radius; }
    std::ostream& print(std::ostream& out) const override {
        return out << "Circle(" << m_center << ", radius " << m_radius << ')';
    }
};

// ── Q2c: raw-pointer version. ─────────────────────────────────────────
int getLargestRadius(const std::vector<Shape*>& shapes) {
    int largest = 0;
    for (const auto* s : shapes) {
        if (const auto* c = dynamic_cast<const Circle*>(s))
            if (c->getRadius() > largest) largest = c->getRadius();
    }
    return largest;
}

// ── Q2d: unique_ptr version — same logic, different ownership. ────────
int getLargestRadius(const std::vector<std::unique_ptr<Shape>>& shapes) {
    int largest = 0;
    for (const auto& s : shapes) {
        if (const auto* c = dynamic_cast<const Circle*>(s.get()))
            if (c->getRadius() > largest) largest = c->getRadius();
    }
    return largest;
}

int main() {
    std::cout << "── Q1: six bugs, fixed ──\n";
    q1a::run();
    q1b::run();
    q1c::run();
    q1d::run();
    q1e::run();
    q1f::run();

    std::cout << "\n── Q2a/b: Shape, Circle, Triangle ──\n";
    Circle c{ Point{ 1, 2 }, 7 };
    std::cout << c << '\n';
    Triangle t{ Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 } };
    std::cout << t << '\n';

    std::cout << "\n── Q2c: vector<Shape*> + getLargestRadius ──\n";
    {
        std::vector<Shape*> shapes;
        shapes.push_back(new Circle{ Point{ 1, 2 }, 7 });
        shapes.push_back(new Triangle{ Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 } });
        shapes.push_back(new Circle{ Point{ 7, 8 }, 3 });

        for (const auto* s : shapes)
            std::cout << *s << '\n';
        std::cout << "The largest radius is: " << getLargestRadius(shapes) << '\n';

        for (auto* s : shapes) delete s;     // manual cleanup
    }

    std::cout << "\n── Q2d: vector<unique_ptr<Shape>> — no raw new/delete ──\n";
    {
        std::vector<std::unique_ptr<Shape>> shapes;
        shapes.push_back(std::make_unique<Circle>(Point{ 1, 2 }, 7));
        shapes.push_back(std::make_unique<Triangle>(Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }));
        shapes.push_back(std::make_unique<Circle>(Point{ 7, 8 }, 3));

        for (const auto& s : shapes)
            std::cout << *s << '\n';
        std::cout << "The largest radius is: " << getLargestRadius(shapes) << '\n';
        // ~unique_ptr frees the shapes; ~Shape is virtual so derived dtors run.
    }
}
