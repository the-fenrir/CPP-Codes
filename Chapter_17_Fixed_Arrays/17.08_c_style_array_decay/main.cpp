// 17.8 — array-to-pointer decay, and the reference-to-array workaround.
#include <cstddef>
#include <iostream>

// Looks like it takes "an array of 5 ints" — actually takes int*.
// The [5] is documentation only. sizeof(arr) here is sizeof(int*) —
// the compiler emits a warning for exactly this reason; we silence it
// locally because demonstrating the trap IS the lesson.
#if defined(__clang__) || defined(__GNUC__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wsizeof-array-argument"
#endif
void byDecay(int arr[5]) {
    std::cout << "byDecay:    sizeof(arr) = " << sizeof(arr) << " (pointer size)\n";
    // for (int x : arr) {} // would not compile — `arr` is int*, no size
}
#if defined(__clang__) || defined(__GNUC__)
# pragma GCC diagnostic pop
#endif

// Reference to array of exactly 5 ints — no decay, real size preserved.
void byRef(int (&arr)[5]) {
    std::cout << "byRef:      sizeof(arr) = " << sizeof(arr)
              << " (" << sizeof(arr)/sizeof(arr[0]) << " elements)\n";
    for (int x : arr) std::cout << "  " << x << '\n';
}

// Templated: accept reference to array of ANY size, deduce N.
template <std::size_t N>
void byRefAnyN(int (&arr)[N]) {
    std::cout << "byRefAnyN:  N = " << N
              << ", first = " << arr[0] << '\n';
}

int main() {
    int arr[5] { 10, 20, 30, 40, 50 };

    std::cout << "in main:    sizeof(arr) = " << sizeof(arr)
              << " (" << sizeof(arr)/sizeof(arr[0]) << " elements)\n";

    byDecay(arr);
    byRef(arr);
    byRefAnyN(arr);

    int small[2] { 1, 2 };
    byRefAnyN(small);   // N = 2 this time — different instantiation
}
