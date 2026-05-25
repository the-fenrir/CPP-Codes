// Chapter 20 quiz solutions.
//   Q1: function prototypes (with trivial bodies + a demo)
//   Q2: discussion — what's wrong with the snippets (see NOTES.md)
//   Q3: binary search — iterative and recursive
#include <iostream>
#include <memory>

// ── Q1a: max(double, double) → double, by value. ─────────────────────
double max(double a, double b) {
    return (a > b) ? a : b;
}

// ── Q1b: swap two ints — references so caller sees the change. ───────
void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// ── Q1c: return by *reference* so the caller can modify the element. ──
// Returns a reference to the largest element in the buffer; caller owns
// the storage and keeps it alive across the call.
int& getLargestElement(int* array, int length) {
    int idx = 0;
    for (int i = 1; i < length; ++i)
        if (array[i] > array[idx]) idx = i;
    return array[idx];
}

// ── Q3a: iterative binary search. ────────────────────────────────────
// `min`/`max` are inclusive index bounds. Returns the index of `target`
// in `array`, or -1 if not present.
int binarySearchIter(const int* array, int target, int min, int max) {
    while (min <= max) {
        // (max - min) / 2 avoids overflow vs. (min + max) / 2.
        int mid = min + (max - min) / 2;
        if (array[mid] == target) return mid;
        if (array[mid]  < target) min = mid + 1;
        else                       max = mid - 1;
    }
    return -1;
}

// ── Q3b: recursive binary search. Same algorithm, different shape. ───
int binarySearchRec(const int* array, int target, int min, int max) {
    if (min > max) return -1;                              // base case — empty range
    int mid = min + (max - min) / 2;
    if (array[mid] == target) return mid;
    if (array[mid]  < target) return binarySearchRec(array, target, mid + 1, max);
    return                           binarySearchRec(array, target, min, mid - 1);
}

int main() {
    std::cout << "── Q1 demos ──\n";
    std::cout << "max(3.5, 2.1) = " << max(3.5, 2.1) << '\n';

    int a = 1, b = 2;
    swap(a, b);
    std::cout << "after swap(a,b): a=" << a << " b=" << b << '\n';

    // Heap-allocated buffer so getLargestElement's reference stays valid.
    auto buf = std::make_unique<int[]>(5);
    buf[0] = 4; buf[1] = 9; buf[2] = 1; buf[3] = 7; buf[4] = 2;
    std::cout << "largest before: " << getLargestElement(buf.get(), 5) << '\n';
    getLargestElement(buf.get(), 5) = -1;                   // assign through the reference
    std::cout << "largest after  zeroing: " << getLargestElement(buf.get(), 5) << '\n';

    std::cout << "\n── Q3: binary search ──\n";
    constexpr int N = 10;
    int sorted[N] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };

    for (int target : { 1, 7, 19, 4, 20 }) {
        int i = binarySearchIter(sorted, target, 0, N - 1);
        int r = binarySearchRec (sorted, target, 0, N - 1);
        std::cout << "target=" << target
                  << "  iter=" << i << "  rec=" << r << '\n';
    }
}
