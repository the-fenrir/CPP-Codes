// 5.8 — std::string_view as a read-only "I'll look at your characters,
//       I won't keep them" type. Binds to literals and std::strings.
#include <iostream>
#include <string>
#include <string_view>

// Read-only string parameter — accepts literals, char arrays, and std::string
// with no copying.
void print(std::string_view s) {
    std::cout << '[' << s << "] length=" << s.length() << '\n';
}

int main() {
    // Binds directly to a string literal — no allocation, no copy.
    std::string_view greeting{ "hello, world" };
    print(greeting);

    // Binds to a std::string. The view does not own; the string still does.
    std::string owned{ "owned by std::string" };
    std::string_view view_of_owned{ owned };
    print(view_of_owned);

    // Substring views are cheap — they're just (ptr, len) pairs into the
    // same backing buffer. No allocation.
    std::string_view first_word{ greeting.substr(0, 5) };
    print(first_word);

    // Pass a literal directly — implicit conversion to string_view.
    print("temporary literal");
}
