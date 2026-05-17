# CPP-Codes — learncpp.com Study Repo

Personal study repo for [learncpp.com](https://www.learncpp.com/) — Chapters 1–15.

Each lesson lives in its own folder with a one-screen `NOTES.md` (cheat-sheet + *why it matters*) plus runnable `.cpp` examples. A single `make` target builds and runs any lesson.

## Chapters

| # | Title | Folder |
|---|---|---|
| 1  | C++ Basics                                  | [Chapter_1_CPP_Basics/](Chapter_1_CPP_Basics/README.md) |
| 2  | Functions and Files                         | [Chapter_2_Functions_and_Files/](Chapter_2_Functions_and_Files/README.md) |
| 3  | Debugging C++ Programs                      | [Chapter_3_Debugging/](Chapter_3_Debugging/README.md) |
| 4  | Fundamental Data Types                      | [Chapter_4_Fundamental_Data_Types/](Chapter_4_Fundamental_Data_Types/README.md) |
| 5  | Constants and Strings                       | [Chapter_5_Constants_and_Strings/](Chapter_5_Constants_and_Strings/README.md) |
| 6  | Operators                                   | [Chapter_6_Operators/](Chapter_6_Operators/README.md) |
| 7  | Scope, Duration, and Linkage                | [Chapter_7_Scope_Duration_Linkage/](Chapter_7_Scope_Duration_Linkage/README.md) |
| 8  | Control Flow                                | [Chapter_8_Control_Flow/](Chapter_8_Control_Flow/README.md) |
| 9  | Error Detection and Handling                | [Chapter_9_Error_Handling/](Chapter_9_Error_Handling/README.md) |
| 10 | Type Conversion, Aliases, and Deduction     | [Chapter_10_Type_Conversion_and_Deduction/](Chapter_10_Type_Conversion_and_Deduction/README.md) |
| 11 | Function Overloading and Templates          | [Chapter_11_Overloading_and_Templates/](Chapter_11_Overloading_and_Templates/README.md) |
| 12 | Compound Types: References and Pointers     | [Chapter_12_References_and_Pointers/](Chapter_12_References_and_Pointers/README.md) |
| 13 | Compound Types: Enums and Structs           | [Chapter_13_Enums_and_Structs/](Chapter_13_Enums_and_Structs/README.md) |
| 14 | Introduction to Classes                     | [Chapter_14_Intro_to_Classes/](Chapter_14_Intro_to_Classes/README.md) |
| 15 | More on Classes                             | [Chapter_15_More_on_Classes/](Chapter_15_More_on_Classes/README.md) |

## Layout

```
.
├── Makefile                          # build & run any lesson
├── common/compile_flags.mk           # shared compiler flags
├── Chapter_1_CPP_Basics/
│   ├── README.md                     # chapter index
│   ├── 1.01_statements_and_structure/
│   │   ├── NOTES.md                  # cheat-sheet
│   │   └── main.cpp                  # runnable example
│   ├── ...                           # one folder per lesson
│   └── 1.x_summary_and_quiz/
│       ├── NOTES.md                  # full chapter recap + full quiz text
│       └── quiz_solutions.cpp        # worked solutions with design commentary
├── Chapter_2_Functions_and_Files/
│   └── ... (same shape)
└── ...                               # one folder per chapter
```

Folders use zero-padded lesson numbers (`1.01`, `1.02`, …, `14.01`, …) so they sort correctly. The lesson ID (e.g. `4.05` or `14.02`) is what you pass to `make`.

Some lessons are multi-file (header + `.cpp`s + `main.cpp`) — the build system auto-detects a `.h` / `.hpp` in the folder and links all `.cpp` files together. This is used in lessons covering header files, separate compilation, internal/external linkage, and out-of-class member/template definitions.

## How to study

The intended loop, one lesson at a time:

1. **Read the learncpp.com lesson.** The site is the source of truth; this repo only complements it.
2. **Skim `NOTES.md`** in the lesson folder — one page, key points + gotchas.
3. **Run the example** with `make 4.05` (or whichever lesson). Read the code alongside the output.
4. **Re-read `NOTES.md`** — the bullets should now click.
5. **At the end of a chapter**, hit `N.x_summary_and_quiz/` — read the whole-chapter cheat-sheet, then solve the official quiz yourself before peeking at `quiz_solutions.cpp`. The summary folders are **self-complete**: full problem statements + expected output + worked answers, so you don't need to flip back to learncpp.com mid-quiz.

## Build & run

Requires GNU `make` and a C++20-capable compiler (`g++` is the default; `clang++` also works).

```
make 4.05          # build & run lesson 4.05
make 14            # build & run every Chapter 14 lesson (smoke test)
make 1             # build & run every Chapter 1 lesson
make list          # print all lesson IDs found on disk
make clean         # remove build/
```

Override the compiler if needed: `make CXX=clang++ 4.05` or `make CXX=g++-13 14.02`.

## Source & credit

All concepts, lesson numbering, and quiz questions come from [learncpp.com](https://www.learncpp.com/) — an excellent free resource. Notes here are my own condensed restatement; nothing is copied verbatim.
