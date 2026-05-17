// 13.2 — Unscoped enumerations: declaring, defaults, custom values, namespacing.
#include <iostream>

// Default-valued enumerators: ogre=0, dragon=1, orc=2, giantSpider=3, slime=4.
enum MonsterType {
    ogre,
    dragon,
    orc,
    giantSpider,
    slime,
};

// Custom-valued: subsequent enumerators count from the last assigned value.
enum HttpStatus {
    ok           = 200,
    created      = 201,    // 201
    badRequest   = 400,
    notFound     = 404,
    serverError  = 500,
};

// Namespacing avoids leaking enumerator names into the global scope.
namespace Animals {
    enum Animal { chicken, dog, cat, elephant, duck, snake };
}

int main() {
    MonsterType m{ slime };
    HttpStatus  s{ notFound };
    Animals::Animal a{ Animals::dog };

    std::cout << "slime as int     = " << m << '\n';   // 4
    std::cout << "notFound as int  = " << s << '\n';   // 404
    std::cout << "dog as int       = " << a << '\n';   // 1

    // Without the Animals:: namespace wrapper, `cat` and `dog` would
    // collide with anything else named `cat` or `dog` in this TU.
}
