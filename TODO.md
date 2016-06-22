# TODO

- `_build_up_roman()` -> `append_to_roman()`
- `arabic_to_roman()` and `roman_{add,subtract}()` alloc but don't free,
  so they should return pointer to non-`const char` (so caller can free)
- test more edge cases
- reduce more duplication
- try on Ubuntu with `gcc`, fixing whatever breaks
- if unit tests `#include "roman_calculator.c"`, can I re-add `static`
  to those units?
- submit!

## Neat ideas

- a fake `malloc()` that can't allocate much, to test-drive failure branches.
  something like:
      void *malloc(size_t n) {
        static size_t total;
        static void *(*omalloc)(size_t);
        if (omalloc == NULL) {
          omalloc = dlsym(RTLD_NEXT, "malloc");
        }
        if (MAX - total < n)
          return NULL;
        total += n; return omalloc(n);
      }
- a corresponding fake `free()` that makes sure the total allocated
  _would_ go back to zero
