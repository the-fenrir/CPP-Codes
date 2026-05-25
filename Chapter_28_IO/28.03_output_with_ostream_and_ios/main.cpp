// 28.3 — formatted output: flags, manipulators, sticky vs. one-shot.
#include <iomanip>
#include <iostream>

int main() {
    // ── flag-level API (setf / unsetf) ────────────────────────────────
    std::cout.setf(std::ios::showpos);
    std::cout << "[flag]    showpos on:  " << 27 << '\n';
    std::cout.unsetf(std::ios::showpos);
    std::cout << "[flag]    showpos off: " << 27 << '\n';

    // ── base manipulators (sticky) ────────────────────────────────────
    std::cout << "[base]    255 dec=" << std::dec << 255
              << " hex=" << std::hex << 255
              << " oct=" << std::oct << 255 << '\n';
    std::cout << std::dec;   // restore — sticky bites later code otherwise

    // ── boolalpha (sticky) ────────────────────────────────────────────
    std::cout << std::boolalpha
              << "[bool]    true=" << true << " false=" << false << '\n'
              << std::noboolalpha;

    // ── floating point: default vs. fixed vs. scientific ──────────────
    const double pi = 3.14159265358979;
    std::cout << "[float]   default(6 sig): " << pi << '\n';
    std::cout << "[float]   fixed,prec=2:   " << std::fixed << std::setprecision(2) << pi << '\n';
    std::cout << "[float]   sci,  prec=3:   " << std::scientific << std::setprecision(3) << pi << '\n';
    std::cout.unsetf(std::ios::floatfield);  // back to default mode
    std::cout << std::setprecision(6);

    // ── width: ONE-SHOT (this is the trap) ────────────────────────────
    std::cout << "[width]   '" << std::setw(8) << 42 << "' next='" << 42 << "'\n";
    //                        ^^^ width=8 applied      ^^^ width reset to 0

    // ── fill + justification ──────────────────────────────────────────
    std::cout << std::setfill('*');
    std::cout << "[just]    right:    '" << std::setw(10) << std::right    << -12345 << "'\n";
    std::cout << "[just]    left:     '" << std::setw(10) << std::left     << -12345 << "'\n";
    std::cout << "[just]    internal: '" << std::setw(10) << std::internal << -12345 << "'\n";
    std::cout << std::setfill(' ');

    // ── a small aligned table: setw before EVERY column ───────────────
    std::cout << "[table]\n";
    struct Row { const char* name; int qty; double price; };
    Row rows[] = { {"apple", 3, 0.5}, {"banana", 12, 0.2}, {"cherry", 100, 0.05} };
    std::cout << std::fixed << std::setprecision(2);
    for (auto& r : rows) {
        std::cout << "  "
                  << std::left  << std::setw(8) << r.name
                  << std::right << std::setw(5) << r.qty
                  << std::right << std::setw(8) << r.price << '\n';
    }
}
