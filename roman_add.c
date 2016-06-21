#include <libgen.h>
#include <stdio.h>
#include "roman_calculator.h"

int main(int argc, char *argv[]) {
    if (argc == 3) {
        printf("%s\n", roman_add(argv[1], argv[2]));
        return 0;
    } else {
        printf("usage: %s <roman-numeral> <roman-numeral>\n", basename(argv[0]));
        return 77;
    }
}
