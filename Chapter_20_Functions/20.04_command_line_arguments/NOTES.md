# 20.4 — Command line arguments

> learncpp.com: https://www.learncpp.com/cpp-tutorial/command-line-arguments/

## Why it matters
Programs need input from outside themselves. For short, scriptable tools, the canonical channel is the command line: arguments after the executable name. Knowing how `main(argc, argv)` is shaped — and that everything arrives as a *string* — is the difference between writing a working CLI and writing one full of subtle parse bugs.

## Key points
- The signature: `int main(int argc, char* argv[])`. `argc` is the count, `argv` is an array of C-string pointers, length `argc + 1` (the last entry is `nullptr`).
- `argv[0]` is the program's invocation path. Real arguments start at `argv[1]`.
- All arguments are **strings**, even `"42"`. Convert with `std::stoi`, `std::stod`, `std::from_chars`, or `std::stringstream` — and check for failure.
- Quoting at the shell level coalesces words: `./prog "hello world"` ⇒ `argv[1] == "hello world"`. Without quotes you get two arguments.
- `std::string_view`/`std::string` on `argv[i]` is fine — they're null-terminated C strings, the conversion is free.
- For non-trivial CLIs, reach for a parser library (CLI11, lyra, argparse). Hand-parsing positional + flag + value combinations gets fragile fast.

## Code in this folder
- `main.cpp` — prints every argument with its index; converts the first one to an int if present.

## Gotchas
- `argc` is `int`, not `size_t`. Loop bounds: `for (int i = 0; i < argc; ++i)`.
- `int n = argv[1];` doesn't compile, and `int n{ argv[1] };` doesn't either — `argv[1]` is `char*`, not an integer. Always go through `std::stoi` (and catch `std::invalid_argument` / `std::out_of_range`).
- `argv[i]` can be reassigned but the underlying memory's lifetime is up to the OS — don't free it, don't write past the null.

## Run
    make 20.04
