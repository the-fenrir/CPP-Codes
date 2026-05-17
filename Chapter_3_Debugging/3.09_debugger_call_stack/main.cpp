// 3.9 — mirrors the structure of quiz Q3 so you can practice reading
// the call stack. The program aborts deliberately inside `d` so you have
// something to backtrace.
//
//   lldb build/3.09/main
//   (lldb) run
//   ...stopped at SIGABRT...
//   (lldb) bt
//
// Expected backtrace (innermost first):
//   frame 0: abort
//   frame 1: d()
//   frame 2: b()
//   frame 3: a()
//   frame 4: main
//
// Try `up` to move from `d`'s frame into `b`'s frame, then `frame variable`
// to inspect `b`'s locals. That's how you investigate "who called this with
// bad arguments?" on a real crash.
#include <cstdlib>
#include <iostream>

void d() {
    std::cerr << "in d() — aborting so you can read the call stack\n";
    std::abort();                       // SIGABRT — debugger catches it
}

void c() {                              // c is called by b but doesn't abort,
    std::cout << "  c() ran\n";         // so you'll only see it if running
}                                       // step-through.

void b() {
    c();
    d();                                // d kills the program here
}

void a() {
    b();
}

int main() {
    std::cout << "main: calling a()\n";
    a();
    std::cout << "main: returned (you won't see this)\n";
}
