// 28.1 — the four standard streams.
//
// All four are predefined global objects. cout/cerr/clog are ostream;
// cin is istream. They differ in their *buffering* policy, which is
// observable when output is interleaved.
#include <iostream>

int main() {
    std::cout << "[cout] line 1 (buffered, flushed at \\n on a tty)\n";
    std::cerr << "[cerr] line 2 (unbuffered — appears immediately)\n";
    std::clog << "[clog] line 3 (buffered, like cout but to stderr)\n";

    // The std::endl manipulator inserts '\n' AND flushes the buffer.
    // For ordinary output, '\n' is cheaper.
    std::cout << "[cout] line 4 with endl" << std::endl;

    // Demonstration: stream objects compose. We're writing to cout, but
    // ANY ostream-derived object would accept exactly the same operators.
    // That's the whole point — files and string streams reuse this.
    std::ostream& sink = std::cout;
    sink << "[cout via ostream& alias] same operator<<, same formatting\n";
}
