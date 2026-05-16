// 15.10 — ref qualifiers: different overloads for lvalue vs rvalue receivers.
#include <iostream>
#include <string>
#include <utility>

class Box {
    std::string m_data;
public:
    Box(std::string d) : m_data{ std::move(d) } {}

    // Lvalue overload: hand back a const& — caller pinky-swears the Box outlives it.
    const std::string& data() const & {
        std::cout << "[lvalue overload] ";
        return m_data;
    }

    // Rvalue overload: object is about to die — move its data out by value.
    std::string data() && {
        std::cout << "[rvalue overload] ";
        return std::move(m_data);
    }
};

Box makeBox() { return Box{ "from temporary" }; }

int main() {
    Box b{ "owned" };
    std::cout << b.data() << '\n';             // lvalue overload

    // Calling data() on a temporary returns by value — no dangling reference.
    std::string s = makeBox().data();
    std::cout << s << '\n';                    // rvalue overload

    // Explicit move to opt in to the rvalue overload on a named object.
    std::string s2 = std::move(b).data();
    std::cout << s2 << '\n';                   // rvalue overload
}
