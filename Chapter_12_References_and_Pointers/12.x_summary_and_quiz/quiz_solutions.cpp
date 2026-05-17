// Chapter 12 quiz solutions.
//   Q1: discussion (see NOTES.md) — lvalue/rvalue classification.
//   Q2: trace of the "ref = y doesn't rebind" program.
//   Q3: demo — const T& vs T& acceptance.
//   Q4: demo — const T* vs T* const.
//   Q5: sort2(int&, int&).
#include <iostream>
#include <utility>

// ── Q2: tracing the trap ────────────────────────────────────────────
// `ref = y;` does NOT rebind ref to y; it assigns y's value into x.
void q2() {
    int x{ 4 };
    int y{ 6 };
    int& ref{ x };
    ++ref;          // x = 5
    ref = y;        // x = 6 (assignment-through-ref, not rebind)
    ++ref;          // x = 7
    std::cout << "Q2: " << x << ' ' << y << "  (expected: 7 6)\n";
}

// ── Q3: const T& accepts strictly more than T& ───────────────────────
// Same body, two parameter types — only one compiles for literals/temporaries.
void readByConstRef(const int& n) { std::cout << "  read: " << n << '\n'; }
// void readByRef(int& n)        — would reject `readByRef(5)` and `readByRef(x+1)`.
void q3() {
    int x{ 10 };
    const int cx{ 20 };
    std::cout << "Q3: const T& accepts...\n";
    readByConstRef(x);           // non-const lvalue: OK
    readByConstRef(cx);          // const lvalue: OK
    readByConstRef(5);           // literal/rvalue: OK (lifetime extension)
    readByConstRef(x + 1);       // rvalue: OK
}

// ── Q5: sort two ints in place ───────────────────────────────────────
// References (not pointers) because the parameters are required, not optional.
// std::swap is idiomatic; a manual swap with a temp would also be fine.
void sort2(int& a, int& b) {
    if (a > b) std::swap(a, b);
}
void q5() {
    int a{ 7 }, b{ 3 };
    sort2(a, b);
    std::cout << "Q5: sort2(7, 3) → a=" << a << " b=" << b << '\n';

    int c{ 1 }, d{ 9 };
    sort2(c, d);                 // already sorted
    std::cout << "Q5: sort2(1, 9) → c=" << c << " d=" << d << '\n';

    int e{ 5 }, f{ 5 };
    sort2(e, f);                 // equal
    std::cout << "Q5: sort2(5, 5) → e=" << e << " f=" << f << '\n';
}

// ── Q4: const T* vs T* const ────────────────────────────────────────
void q4() {
    int x{ 1 }, y{ 2 };

    // pointer to const: repoint OK, no modify through it
    const int* p_to_const{ &x };
    // *p_to_const = 5;          // error
    p_to_const = &y;             // OK
    std::cout << "Q4: const int*  → *p = " << *p_to_const
              << "  (repointable, pointee read-only)\n";

    // const pointer: modify through it OK, repoint not OK
    int* const const_p{ &x };
    *const_p = 5;                // OK
    // const_p = &y;             // error
    std::cout << "Q4: int* const  → x  = " << x
              << "  (locked target, pointee writable)\n";
}

int main() {
    q2();
    q3();
    q4();
    q5();
}
