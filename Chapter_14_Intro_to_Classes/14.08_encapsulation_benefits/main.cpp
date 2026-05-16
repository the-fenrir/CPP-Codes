// 14.8 — the payoff: swap internals without touching callers.
#include <iostream>
#include <vector>
#include <deque>     // ← demonstrate that internals can change.

class Stack {
    // First impl: vector.        Second impl (commented): deque.
    std::vector<int> m_data;
    // std::deque<int>  m_data;
public:
    void push(int v) { m_data.push_back(v); }
    int  pop()       { int v = m_data.back(); m_data.pop_back(); return v; }
    bool empty() const { return m_data.empty(); }
    int  size()  const { return static_cast<int>(m_data.size()); }
};

int main() {
    Stack s;
    s.push(1); s.push(2); s.push(3);
    std::cout << "size=" << s.size() << '\n';
    while (!s.empty()) std::cout << s.pop() << ' ';
    std::cout << '\n';
    // The caller code above is unchanged whether m_data is vector OR deque.
    // That's the whole point.
}
