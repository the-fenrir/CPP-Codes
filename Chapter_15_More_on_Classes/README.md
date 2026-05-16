# Chapter 15 — More on Classes

Chapter 15 fills in the rest of the class machinery: the hidden `this` pointer, header/source separation, nested types, destructors, class templates, static members, friends, and ref qualifiers. Where chapter 14 was "what is a class," chapter 15 is "the toolbox for building real ones."

## Lessons

| # | Lesson |
|---|---|
| 15.01 | [The hidden `this` pointer & member-function chaining](15.01_this_pointer_and_chaining/NOTES.md) |
| 15.02 | [Classes and header files](15.02_classes_and_header_files/NOTES.md) |
| 15.03 | [Nested types (member types)](15.03_nested_types/NOTES.md) |
| 15.04 | [Introduction to destructors](15.04_destructors/NOTES.md) |
| 15.05 | [Class templates with member functions](15.05_class_templates_with_member_functions/NOTES.md) |
| 15.06 | [Static member variables](15.06_static_member_variables/NOTES.md) |
| 15.07 | [Static member functions](15.07_static_member_functions/NOTES.md) |
| 15.08 | [Friend non-member functions](15.08_friend_non_member_functions/NOTES.md) |
| 15.09 | [Friend classes and friend member functions](15.09_friend_classes_and_friend_members/NOTES.md) |
| 15.10 | [Ref qualifiers](15.10_ref_qualifiers/NOTES.md) |
| 15.x | [Summary & quiz](15.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear, but groups:

- **15.01–15.02** — mechanics (`this`, header/source split). Both are short; do them back-to-back.
- **15.04** — destructors. Tiny lesson, huge implications for RAII (which the site will build on later).
- **15.05** — class templates. If you've done function templates, this is the natural extension; pace yourself, the syntax is gnarly.
- **15.06–15.07** — static members are a pair; do not split.
- **15.08–15.09** — friends. Read 14.5–14.8 again first if encapsulation feels fuzzy; friend bypasses it.
- **15.10** — ref qualifiers. The most "advanced" topic in these two chapters; pairs back with 14.7.
