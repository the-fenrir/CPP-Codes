// 7.7 — the single defining TU for each external-linkage global.
#include "globals.h"

int g_counter{ 0 };                 // definition
extern const int g_max{ 100 };      // definition (initializer present)
