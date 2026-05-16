// 15.3 — nested struct (private), nested enum (public), nested type alias.
#include <iostream>

class IntStack {
    struct Node {              // private nested type — implementation detail
        int value;
        Node* next;
    };

    Node* m_head{ nullptr };
public:
    enum class State { Empty, NonEmpty };   // public nested enum — part of the interface

    using value_type = int;                  // public nested alias — idiomatic

    ~IntStack() {
        while (m_head) { Node* n = m_head; m_head = m_head->next; delete n; }
    }

    void push(value_type v) { m_head = new Node{ v, m_head }; }

    State state() const { return m_head ? State::NonEmpty : State::Empty; }

    void print() const {
        for (Node* n = m_head; n; n = n->next) std::cout << n->value << ' ';
        std::cout << '\n';
    }
};

int main() {
    IntStack s;
    std::cout << "empty? " << (s.state() == IntStack::State::Empty) << '\n';

    s.push(1); s.push(2); s.push(3);
    s.print();
    std::cout << "empty? " << (s.state() == IntStack::State::Empty) << '\n';
}
