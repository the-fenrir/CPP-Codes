// 2.12 — gadget implementation.
#include "gadget.h"
#include <iostream>

void useGadget(const Gadget& g) {
    std::cout << "gadget wrapping ";
    useWidget(g.core);
}
