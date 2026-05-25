// 27.2 — minimal try / throw / catch, plus catch-by-reference and catch order.
#include <iostream>
#include <stdexcept>
#include <string>

int main() {
    // ── (1) the basic shape ────────────────────────────────────────
    try {
        throw 7; // throw any copy-constructible value
    } catch (int x) {
        std::cout << "caught int = " << x << '\n';
    }

    // ── (2) different types, multiple catches, first-match-wins ────
    auto run = [](int which) {
        try {
            if      (which == 1) throw 42;
            else if (which == 2) throw std::string{ "oops" };
            else                 throw std::runtime_error{ "boom" };
        } catch (int x) {
            std::cout << "  int    -> " << x << '\n';
        } catch (const std::string& s) {       // catch class types by const&
            std::cout << "  string -> " << s << '\n';
        } catch (const std::exception& e) {     // catches runtime_error too
            std::cout << "  exc    -> " << e.what() << '\n';
        }
    };

    std::cout << "case 1:\n"; run(1);
    std::cout << "case 2:\n"; run(2);
    std::cout << "case 3:\n"; run(3);

    // ── (3) execution after handler resumes AFTER the last catch ───
    std::cout << "done\n";
    return 0;
}
