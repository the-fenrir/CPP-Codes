# Chapter 28 — Input and Output (I/O)

Chapter 28 is the practical tour of the `<iostream>` / `<sstream>` / `<fstream>` machinery you've been using since chapter 1. You move from the conceptual stream model to the actual classes, their state flags, formatting controls, and finally to file I/O — including random access. By the end you can validate user input cleanly, format output deterministically, and read/write files (sequentially or at arbitrary positions).

## Lessons

| # | Lesson |
|---|---|
| 28.01 | [Input and output (I/O) streams](28.01_io_streams/NOTES.md) |
| 28.02 | [Input with istream](28.02_input_with_istream/NOTES.md) |
| 28.03 | [Output with ostream and ios](28.03_output_with_ostream_and_ios/NOTES.md) |
| 28.04 | [Stream classes for strings](28.04_stream_classes_for_strings/NOTES.md) |
| 28.05 | [Stream states and input validation](28.05_stream_states_and_input_validation/NOTES.md) |
| 28.06 | [Basic file I/O](28.06_basic_file_io/NOTES.md) |
| 28.07 | [Random file I/O](28.07_random_file_io/NOTES.md) |
| 28.x | [Summary & recap](28.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear. The chapter splits cleanly into three blocks:

- **28.01 → 28.03** — the stream model itself: hierarchy, extraction, insertion, formatting. 28.03 is where most beginners get tripped up by the difference between sticky flags (`std::hex`, `std::fixed`) and one-shot manipulators (`std::setw`).
- **28.04 → 28.05** — `stringstream` and stream state. These two together give you the modern recipe for input validation: extract to a `std::string`, parse with a `stringstream` or `std::from_chars`, never trust `std::cin >>` directly.
- **28.06 → 28.07** — file I/O. 28.06 covers the common case (open, read/write lines, close via RAII); 28.07 covers `seekg`/`seekp` and the read+write `fstream` pattern (which is binary-mode territory in practice).

learncpp.com does not publish a Chapter 28 summary/quiz page — 28.x in this repo is a one-page recap plus a small end-to-end demo.
