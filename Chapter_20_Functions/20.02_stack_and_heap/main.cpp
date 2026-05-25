// 20.2 — stack vs. heap: where locals live, where `new` puts things,
//        and why returning a pointer to a local is a bug.
#include <iostream>
#include <memory>

// Stack: `local` lives in this function's frame. The address printed
// is reused by later calls — proof the frame is reclaimed on return.
void stackFrame(int tag) {
    int local = tag;
    std::cout << "  stack local @ " << static_cast<const void*>(&local)
              << " = " << local << '\n';
}

// Heap: caller is responsible for cleanup. Returning unique_ptr makes
// ownership impossible to forget.
std::unique_ptr<int> makeHeapInt(int value) {
    return std::make_unique<int>(value);
}

int main() {
    std::cout << "── stack frames are reused ──\n";
    stackFrame(1);
    stackFrame(2);  // typically prints the same address as above

    std::cout << "\n── heap survives the function that allocated it ──\n";
    auto p = makeHeapInt(42);
    std::cout << "  heap @ " << static_cast<const void*>(p.get())
              << " = " << *p << '\n';

    std::cout << "\n── big buffers belong on the heap ──\n";
    // 4 million ints on the stack would blow most stacks. On the heap it's
    // fine. (std::vector is heap-backed under the hood.)
    auto big = std::make_unique<int[]>(4'000'000);
    big[1'999'999] = 7;
    std::cout << "  big[1999999] = " << big[1'999'999] << '\n';
}
