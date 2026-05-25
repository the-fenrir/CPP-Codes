// 16.11 — vector as a stack: paren-matching with push_back / back / pop_back.
#include <iostream>
#include <string_view>
#include <vector>

bool balanced(std::string_view s) {
    std::vector<char> stack;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push_back(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (stack.empty()) return false;
            char open{ stack.back() };
            stack.pop_back();
            if ((c == ')' && open != '(') ||
                (c == ']' && open != '[') ||
                (c == '}' && open != '{')) return false;
        }
    }
    return stack.empty();
}

int main() {
    for (std::string_view s : { "()", "([])", "({[]})", "(", "([)]", "" }) {
        std::cout << '"' << s << "\" -> "
                  << (balanced(s) ? "balanced" : "NOT balanced") << '\n';
    }
}
