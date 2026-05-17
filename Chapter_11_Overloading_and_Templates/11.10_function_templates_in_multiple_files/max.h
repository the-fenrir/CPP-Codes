// 11.10 — template body lives in the header so every TU can instantiate it.
#pragma once

template <typename T>
T my_max(T a, T b) {
    return (a < b) ? b : a;
}
