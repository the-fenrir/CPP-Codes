// 5.9 — string_view part 2: shrink-from-the-ends, copy-out, and the
//       dangling-view trap (kept commented to stay UB-free at runtime).
#include <iostream>
#include <string>
#include <string_view>

// Returning a string_view to a local std::string is the classic bug.
// std::string_view returnsDangling() {
//     std::string s{ "I die at function return" };
//     return s;        // view to s — s is destroyed at this very statement
// }

// Safe: returns an owning copy.
std::string returnsOwning() {
    return std::string{ "I live as long as the caller wants me to" };
}

int main() {
    // remove_prefix / remove_suffix: shrink the window without copying.
    std::string_view path{ "/usr/local/bin/" };
    std::cout << "before:           [" << path << "]\n";
    path.remove_prefix(1);   // drop leading '/'
    path.remove_suffix(1);   // drop trailing '/'
    std::cout << "after trimming:   [" << path << "]\n";

    // Copy out of a view into an owning string when you need lifetime safety.
    std::string copied{ path };           // allocates; owns its own chars
    std::cout << "owned copy:       [" << copied << "]\n";

    // Safe owning return — no dangling, no view.
    std::cout << "owning result:    [" << returnsOwning() << "]\n";

    // The dangling case, kept as commentary only:
    //   std::string_view bad{ returnsOwning() };  // returnsOwning()'s
    //   std::cout << bad;                         // result dies at ';' above;
    //                                             // reading `bad` is UB.
}
