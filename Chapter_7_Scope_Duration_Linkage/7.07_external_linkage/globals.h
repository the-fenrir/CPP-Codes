// 7.7 — forward declarations only. NO definitions in this header.
#pragma once

extern int g_counter;               // non-const: external by default
extern const int g_max;             // const: must say `extern` to share it
