// 7.6 — `static` at file scope ⇒ internal linkage.
// This `s_count` is invisible to b.cpp.
#include "internal.h"

static int s_count{ 0 };

void bump_in_a() { ++s_count; }
int  read_in_a() { return s_count; }
