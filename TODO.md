# Neat ideas

- test more edge cases
- feed test results into Eclipse test runner for red/green
- alternate implementation: no intermediate arabic numerals!
- a fake `malloc()` that can't allocate much, to test-drive failure branches.
  something like:
  ```c_cpp
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
  ```
- a corresponding fake `free()` that makes sure the total allocated
  _would_ go back to zero
