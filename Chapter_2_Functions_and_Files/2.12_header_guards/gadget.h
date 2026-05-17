// 2.12 — pragma once style. Note we also include widget.h here, which means
// any TU that includes both gadget.h and widget.h sees widget.h twice — the
// guard in widget.h is what keeps that legal.
#pragma once
#include "widget.h"

struct Gadget {
    Widget core;
};

void useGadget(const Gadget& g);
