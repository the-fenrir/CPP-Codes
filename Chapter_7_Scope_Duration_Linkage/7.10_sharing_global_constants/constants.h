// 7.10 — `inline constexpr` shared across every TU that includes this header.
#pragma once

namespace Constants {
    inline constexpr double pi   { 3.14159265358979323846 };
    inline constexpr double e    { 2.71828182845904523536 };
    inline constexpr int    g_max_class_size{ 35 };
}
