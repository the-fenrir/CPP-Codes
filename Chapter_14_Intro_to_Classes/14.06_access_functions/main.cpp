// 14.6 — getters, validated setters, and computed access functions.
#include <iostream>

class Temperature {
    double m_celsius{ 0 };
public:
    double celsius()    const { return m_celsius; }
    double fahrenheit() const { return m_celsius * 9.0 / 5.0 + 32.0; }  // computed — better than exposing m_celsius raw.

    void setCelsius(double c) {
        if (c < -273.15) c = -273.15;  // setter earns its keep: validation.
        m_celsius = c;
    }
};

int main() {
    Temperature t;
    t.setCelsius(100);
    std::cout << t.celsius() << "°C = " << t.fahrenheit() << "°F\n";

    t.setCelsius(-9999);  // clamped
    std::cout << "after invalid set: " << t.celsius() << "°C\n";
}
