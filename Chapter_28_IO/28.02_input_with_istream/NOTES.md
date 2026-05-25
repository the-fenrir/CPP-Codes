# 28.2 — Input with istream

> learncpp.com: https://www.learncpp.com/cpp-tutorial/input-with-istream/

## Why it matters
`std::cin >> x` looks simple and hides three traps: it skips leading whitespace, it stops at the *next* whitespace, and it leaves the rest (including the trailing `'\n'`) in the buffer for the next read. This lesson catalogs the tools that let you control whitespace, line endings, and how much you consume — the prerequisites for any serious input handling.

## Key points
- **`operator>>`** — skips leading whitespace, extracts until the next whitespace. For C-strings, vulnerable to buffer overflow; use `std::setw(N)` to cap.
- **`get(ch)`** / **`get(buf, N)`** — does *not* skip whitespace, does *not* discard the delimiter. The string form stops on `'\n'` (or specified delimiter) and leaves it in the stream.
- **`getline(buf, N)`** / **`std::getline(std::cin, str)`** — like `get`, but *consumes and discards* the delimiter. The non-member form for `std::string` is the one you actually want.
- **`gcount()`** — characters extracted by the most recent unformatted input call (`get`, `getline`, `read`, `ignore`).
- **`ignore(n, delim)`** — discard up to `n` characters or until `delim`. Classic recovery idiom:
  `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');`
- **`peek()`** — look at the next character without removing it.
- **`unget()`** — push back the last extracted character.
- **`putback(ch)`** — push back a specific character (need not be the one just read).
- **`std::ws`** — manipulator that explicitly skips whitespace; useful before a `getline` that follows a `>>`.

## Code in this folder
- `main.cpp` — drives the istream API against a `std::istringstream` so it runs non-interactively. Demonstrates `>>` vs `get` vs `getline`, the `>>` + `getline` whitespace bug, and `peek`/`unget`.

## Gotchas
- **The classic mixed-mode bug:** `std::cin >> n;` followed by `std::getline(std::cin, line);` — `getline` immediately returns an empty string because `>>` left the `'\n'` behind. Fix with `std::cin >> std::ws` or `cin.ignore(..., '\n')` between them.
- `getline` with a *C-string* buffer leaves the stream in a fail state if the input exceeded the buffer; the non-member `std::string` version does not.
- `peek()` returns `int`, not `char` — it has to be able to return `EOF` (-1).

## Run
    make 28.02
