# CPP-Codes — learncpp.com Study Repo

Personal study repo for [learncpp.com](https://www.learncpp.com/) — currently covering **Chapter 14 (Introduction to Classes)** and **Chapter 15 (More on Classes)**.

Each lesson lives in its own folder with a one-screen `NOTES.md` (cheat-sheet + *why it matters*) plus runnable `.cpp` examples. A single `make` target builds and runs any lesson.

## Layout

```
.
├── Makefile                          # build & run any lesson
├── common/compile_flags.mk           # shared compiler flags
├── Chapter_14_Intro_to_Classes/
│   ├── README.md                     # chapter index
│   ├── 14.01_intro_to_oop/
│   │   ├── NOTES.md                  # cheat-sheet
│   │   └── main.cpp                  # runnable example
│   ├── 14.02_intro_to_classes/
│   │   ├── NOTES.md
│   │   └── main.cpp
│   ├── ...                           # one folder per lesson
│   └── 14.x_summary_and_quiz/
│       ├── NOTES.md
│       └── quiz_solutions.cpp
└── Chapter_15_More_on_Classes/
    └── ... (same shape)
```

Folders use zero-padded lesson numbers (`14.01`, `14.02`, …) so they sort correctly. The lesson ID (e.g. `14.02`) is what you pass to `make`.

## How to study

The intended loop, one lesson at a time:

1. **Read the learncpp.com lesson.** The site is the source of truth; this repo only complements it.
2. **Skim `NOTES.md`** in the lesson folder — one page, key points + gotchas.
3. **Run the example** with `make 14.02` (or whichever lesson). Read the code alongside the output.
4. **Re-read `NOTES.md`** — the bullets should now click.
5. **At the end of a chapter**, hit `14.x_summary_and_quiz/` — read the whole-chapter cheat-sheet, then solve the official quiz yourself before peeking at `quiz_solutions.cpp`.

## Build & run

Requires GNU `make` and a C++20-capable compiler (Apple `clang++` or `g++`).

```
make 14.02         # build & run lesson 14.02
make 14            # build & run every Chapter 14 lesson (smoke test)
make 15            # build & run every Chapter 15 lesson
make list          # print all lesson IDs found on disk
make clean         # remove build/
```

Override the compiler if needed: `make CXX=g++-13 14.02`.

## Source & credit

All concepts, lesson numbering, and quiz questions come from [learncpp.com](https://www.learncpp.com/) — an excellent free resource. Notes here are my own condensed restatement; nothing is copied verbatim.
