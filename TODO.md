# TODO

- check for `malloc()` failure
- `void _build_up_roman(char **romanp)` and then `_build_up_roman(&roman)`
- `_build_up_roman()` -> `append_to_roman()`
- `malloc()` enough space for a trailing `'\0'`
- `malloc(0)` should be `malloc(1)`, and put a `'\0'` in it
- replace the repeated `malloc()/strlcpy()` with `realloc()`
- replace `strcpy()/strcat()` with `strlcpy()/strlcat()`
- `arabic_to_roman()` and `roman_{add,subtract}()` alloc but don't free,
  so they should return pointer to non-`const char` (so caller can free)
- test more edge cases
- reduce more duplication
- try on Ubuntu with gcc, fixing whatever breaks
- submit!
