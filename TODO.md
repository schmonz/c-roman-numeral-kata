# Neat ideas

- Test that we can't have four I (etc.) in a row.
- Test overflow and underflow (both Roman and Arabic).
- Maybe use a union for exception conditions?
- Fix memory leaks found by Valgrind.
- What are `.PHONY` and all that about?
- Everything `uwe@` said.
- Test that we handle `malloc` failure, via a fake like:

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
- Test that we `free` what we `malloc`.
- Use `automake` and `autoconf`
- Build the library with `libtool`.
- Extract tests, library code, application code to separate subdirs.
- Link with local `strlcat` (etc.) definition where needed.
- Run tests from Eclipse test runner (via TAP).
- Try reimplementing _without_ intermediate Arabic numerals!
