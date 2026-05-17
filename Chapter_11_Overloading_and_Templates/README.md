# Chapter 11 — Function Overloading and Function Templates

Chapter 11 covers the two C++ mechanisms for giving one name to many related operations: **function overloading** (multiple functions with the same name but different parameters, resolved at compile time) and **function templates** (one description that instantiates into many concrete functions on demand). Along the way: how the compiler picks an overload, when matches are ambiguous, how to forbid bad calls with `= delete`, default arguments, and the multi-file rules templates impose.

## Lessons

| # | Lesson |
|---|---|
| 11.01 | [Introduction to function overloading](11.01_intro_to_function_overloading/NOTES.md) |
| 11.02 | [Function overload differentiation](11.02_overload_differentiation/NOTES.md) |
| 11.03 | [Function overload resolution and ambiguous matches](11.03_overload_resolution_and_ambiguity/NOTES.md) |
| 11.04 | [Deleting functions](11.04_deleting_functions/NOTES.md) |
| 11.05 | [Default arguments](11.05_default_arguments/NOTES.md) |
| 11.06 | [Function templates](11.06_function_templates/NOTES.md) |
| 11.07 | [Function template instantiation](11.07_function_template_instantiation/NOTES.md) |
| 11.08 | [Function templates with multiple template types](11.08_function_templates_with_multiple_template_types/NOTES.md) |
| 11.09 | [Non-type template parameters](11.09_non_type_template_parameters/NOTES.md) |
| 11.10 | [Using function templates in multiple files](11.10_function_templates_in_multiple_files/NOTES.md) |
| 11.x | [Summary & quiz](11.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear. Two clusters worth special attention:

- **11.01 → 11.03** — overloading is easy to use and easy to misuse. 11.03 (the resolution algorithm) is the lesson that explains *why* an innocent-looking call won't compile or quietly picks the wrong overload.
- **11.06 → 11.10** — templates. 11.06–11.07 set up the model (write once, instantiate per use). 11.10 is the practical consequence: templates must live in headers.
