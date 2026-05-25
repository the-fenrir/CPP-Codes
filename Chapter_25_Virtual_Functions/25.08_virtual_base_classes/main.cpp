// 25.8 — diamond inheritance, resolved with `virtual` on the shared base.
#include <iostream>

class PoweredDevice {
public:
    PoweredDevice(int power) {
        std::cout << "  PoweredDevice(" << power << ")\n";
    }
};

// `virtual` on the base → there will be at most one PoweredDevice sub-object
// regardless of how many paths reach it from below.
class Scanner : virtual public PoweredDevice {
public:
    Scanner(int scanner, int power) : PoweredDevice{ power } {
        std::cout << "  Scanner(" << scanner << ")\n";
    }
};

class Printer : virtual public PoweredDevice {
public:
    Printer(int printer, int power) : PoweredDevice{ power } {
        std::cout << "  Printer(" << printer << ")\n";
    }
};

// Most-derived class is responsible for constructing the virtual base.
// The PoweredDevice calls in Scanner/Printer's init lists are ignored here.
class Copier : public Scanner, public Printer {
public:
    Copier(int scanner, int printer, int power)
        : PoweredDevice{ power }      // most-derived initializes virtual base
        , Scanner{ scanner, power }
        , Printer{ printer, power }
    {
        std::cout << "  Copier()\n";
    }
};

int main() {
    std::cout << "Constructing Copier{1,2,3}:\n";
    Copier c{ 1, 2, 3 };
    // PoweredDevice runs ONCE. With non-virtual inheritance you'd see it twice.
}
