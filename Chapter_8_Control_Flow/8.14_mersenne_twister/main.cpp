// 8.14 — Mersenne Twister via <random>: the standard everyday pattern.
//        We DON'T use the site's Random.h header — same idea, inlined so this
//        folder builds standalone.
#include <iostream>
#include <random>

// Roll one die with N sides. Holds a single engine across calls via `static`,
// so seeding happens exactly once per program run. The distribution is cheap
// to construct so we make it per-call.
int rollDie(int sides) {
    static std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<int> dist{ 1, sides };
    return dist(mt);
}

double normalSample(double mean, double stddev) {
    static std::mt19937 mt{ std::random_device{}() };
    std::normal_distribution<double> dist{ mean, stddev };
    return dist(mt);
}

int main() {
    std::cout << "ten d6: ";
    for (int i = 0; i < 10; ++i) std::cout << rollDie(6) << ' ';
    std::cout << '\n';

    std::cout << "five d20: ";
    for (int i = 0; i < 5; ++i) std::cout << rollDie(20) << ' ';
    std::cout << '\n';

    std::cout << "five N(0,1) samples: ";
    for (int i = 0; i < 5; ++i)
        std::cout << normalSample(0.0, 1.0) << ' ';
    std::cout << '\n';
}
