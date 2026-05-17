// 2.12 — including widget.h twice (directly + transitively via gadget.h) is
// fine because of the header guard. Without the guard, `struct Widget` would
// be redefined in this TU and the compile would fail.
#include "widget.h"
#include "gadget.h"
#include <iostream>

int main() {
    Widget w{ 1 };
    Gadget g{ Widget{ 2 } };
    useWidget(w);
    useGadget(g);
}
