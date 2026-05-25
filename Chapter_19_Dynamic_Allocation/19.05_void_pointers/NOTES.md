# 19.5 — Void pointers

> learncpp.com: https://www.learncpp.com/cpp-tutorial/void-pointers/

## Why it matters
A `void*` is a pointer that has dropped its type information — it can point at *any* object but it can't be dereferenced or arithmetic'd without first being cast back to a real pointer type. It's the type-erasure mechanism the C standard library was built on (`memcpy`, `qsort`, `malloc`). You'll see it in legacy code, OS interfaces, and "generic" callback APIs. In C++ it's almost always the wrong tool: templates, `std::variant`, `std::any`, and inheritance solve the same problems while keeping the type system on your side.

## Key points
- A `void*` holds *the address* but not *the type*. The compiler refuses `*pv` and `pv++`.
- To use it you must `static_cast` back to the original pointer type. Casting to the *wrong* type is undefined behavior; the compiler can't help.
- Conversion from `T*` to `void*` is implicit. Conversion back is *not* — you must spell it out, exactly because it's dangerous.
- `nullptr` can be assigned to a `void*`. "Null pointer" describes a *value*; "void pointer" describes a *type*. A pointer can be both at once.
- Common (legacy) appearances: `void* malloc(size_t)`, `void* memcpy(void*, const void*, size_t)`, `qsort`'s comparator argument, `pthread_create`'s `void* (*start)(void*)`.

## Code in this folder
- `main.cpp` — store `int*`, `double*`, and `const char*` addresses in the same `void*`, then dispatch on a tag and cast back to print each one. Comment block explains why this is exactly the mechanism `std::variant` replaces.

## Gotchas
- `static_cast<T*>(pv)` only makes sense if `pv` actually points to a `T`. You're vouching for that yourself; nothing else can.
- `delete` on a raw `void*` is undefined behavior — the runtime doesn't know what destructor to run. Always cast back to the real type first.
- Pointer arithmetic on `void*` is non-standard (some compilers treat it as `char*` for convenience; don't rely on it).
- Modern alternative: if you need "this variable holds one of these specific types," use `std::variant<int, double, std::string>` and `std::visit`. If you need "any type at all" with runtime type-id, use `std::any`. Both keep the type system involved; `void*` does not.

## Run
    make 19.05
