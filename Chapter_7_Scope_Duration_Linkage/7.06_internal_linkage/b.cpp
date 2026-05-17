// 7.6 — same identifier `s_count`, but internal linkage in each TU means
// these are two distinct variables that never collide at link time.
#include "internal.h"

static int s_count{ 0 };

void bump_in_b() { s_count += 10; }
int  read_in_b() { return s_count; }
