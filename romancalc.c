#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "roman_calculator.h"

static int usage(char *progname) {
    printf("usage: %s <roman-numeral> <+-> <roman-numeral>\n", basename(progname));
    return 77;
}

int main(int argc, char *argv[]) {
    const char *(*fp)(const char *, const char *);
    if (argc == 4) {
        if (0 == strcmp(argv[2], "+")) {
            fp = &roman_add;
        } else if (0 == strcmp(argv[2], "-")) {
            fp = &roman_subtract;
        } else {
            return usage(argv[0]);
        }
        printf("%s\n", fp(argv[1], argv[3]));
        return 0;
    } else {
        return usage(argv[0]);
    }
}
