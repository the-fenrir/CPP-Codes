// 2.7 — forward declaration lets us call a function defined later in the file.
#include <iostream>

int add(int x, int y);               // forward declaration (prototype)

int main() {
    std::cout << "3 + 4 = " << add(3, 4) << '\n';
}

// Definition appears after main(); without the prototype above, this would
// not compile because `add` would be unknown at the point of the call.
int add(int x, int y) {
    return x + y;
}
