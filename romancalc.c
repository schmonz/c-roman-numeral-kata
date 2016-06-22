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
    if (argc == 4) {
        switch (argv[2][0]) {
            case '+':
                printf("%s\n", roman_add(argv[1], argv[3]));
                break;
            case '-':
                printf("%s\n", roman_subtract(argv[1], argv[3]));
                break;
            default:
                return usage(argv[0]);
        }
        return 0;
    } else {
        return usage(argv[0]);
    }
}
