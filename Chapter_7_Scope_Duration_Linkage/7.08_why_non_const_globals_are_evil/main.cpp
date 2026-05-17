// 7.8 — non-const globals couple functions invisibly.
#include <iostream>

int g_discount{ 0 };                 // a "small convenience" global

int price_after_discount(int base) {
    return base - (base * g_discount) / 100;
}

void apply_holiday_sale() {
    g_discount = 30;                 // side effect: mutates global state
}

void reset_pricing() {
    g_discount = 0;
}

int main() {
    // Same input (base=100), three different answers depending on
    // whatever previous function happened to run. Nothing in
    // price_after_discount()'s signature warns you of this.
    std::cout << "fresh:               " << price_after_discount(100) << '\n';
    apply_holiday_sale();
    std::cout << "after holiday sale:  " << price_after_discount(100) << '\n';
    reset_pricing();
    std::cout << "after reset:         " << price_after_discount(100) << '\n';

    std::cout << "\nThe function looks pure from its signature,\n"
                 "but its result depends on call history. That's the bug.\n";
}
