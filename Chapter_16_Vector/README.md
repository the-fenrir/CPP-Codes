# Chapter 16 — Dynamic arrays: std::vector

Chapter 16 leaves single-object thinking behind and introduces **containers** — the STL way to hold many values of the same type. The chapter centers on `std::vector`: how to build one, pass and return it, iterate it, grow and shrink it, and use it as a stack. The recurring theme is the **signed/unsigned mismatch** between `int` loop variables and `size_t` indices, and how to write loops that don't blow up at the boundary.

## Lessons

| # | Lesson |
|---|---|
| 16.01 | [Introduction to containers and arrays](16.01_intro_to_containers_and_arrays/NOTES.md) |
| 16.02 | [Introduction to `std::vector` and list constructors](16.02_intro_to_vector_and_list_constructors/NOTES.md) |
| 16.03 | [`std::vector` and the unsigned length & subscript problem](16.03_vector_unsigned_length_subscript/NOTES.md) |
| 16.04 | [Passing `std::vector`](16.04_passing_vector/NOTES.md) |
| 16.05 | [Returning `std::vector`, and an intro to move semantics](16.05_returning_vector_move_semantics/NOTES.md) |
| 16.06 | [Arrays and loops](16.06_arrays_and_loops/NOTES.md) |
| 16.07 | [Arrays, loops, and sign challenge solutions](16.07_arrays_loops_sign_challenge/NOTES.md) |
| 16.08 | [Range-based for loops (for-each)](16.08_range_based_for_loops/NOTES.md) |
| 16.09 | [Array indexing and length using enumerators](16.09_array_indexing_with_enumerators/NOTES.md) |
| 16.10 | [`std::vector` resizing and capacity](16.10_vector_resizing_and_capacity/NOTES.md) |
| 16.11 | [`std::vector` and stack behavior](16.11_vector_stack_behavior/NOTES.md) |
| 16.12 | [`std::vector<bool>`](16.12_vector_bool/NOTES.md) |
| 16.x | [Summary & quiz](16.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear, but groups:

- **16.01–16.02** — the container concept and the constructors that fill one. Get CTAD right here; the rest of the chapter relies on it.
- **16.03 → 16.07** — the **signed/unsigned saga**. `size()` is unsigned, your loop counter wants to be signed, and underflow eats you alive. 16.03 names the problem, 16.06 shows the standard loops, 16.07 collects the workable solutions. Do them as a block.
- **16.04–16.05** — passing and returning. Read these together; 16.05 is the first real exposure to **move semantics** and that's the bigger idea (it returns in Ch. 22).
- **16.08–16.09** — sugar for traversal and indexing. 16.08 (range-for) is the loop you'll actually write 90% of the time.
- **16.10–16.11** — **length vs. capacity** is the model that makes `push_back` make sense. Don't skip 16.11; stack behavior is how vectors are used in practice.
- **16.12** — `vector<bool>` is the cautionary tale. Short, but worth reading so you don't get surprised.
