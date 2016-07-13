#include <err.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "roman_calculator.h"

#define NULL_BYTE_LENGTH 1

struct a2r {
    const arabic_t arabic;
    const char *roman;
};

const struct a2r A2R[] = {
    { 1000,  "M" },
    {  900, "CM" },
    {  500,  "D" },
    {  400, "CD" },
    {  100,  "C" },
    {   90, "XC" },
    {   50,  "L" },
    {   40, "XL" },
    {   10,  "X" },
    {    9, "IX" },
    {    5,  "V" },
    {    4, "IV" },
    {    1,  "I" }
};
const size_t A2R_LENGTH = sizeof(A2R) / sizeof(A2R[0]);

static arabic_t roman_digit_to_arabic(const char roman_digit) {
    const char as_string[] = { roman_digit, '\0' };

    for (size_t i = 0; i < A2R_LENGTH; i++)
        if (0 == strcmp(as_string, A2R[i].roman))
            return A2R[i].arabic;

    return INVALID_ROMAN_NUMERAL;
}

static const char * arabic_increment_to_roman(arabic_t arabic_increment) {
    for (size_t i = 0; i < A2R_LENGTH; i++)
        if (arabic_increment == A2R[i].arabic)
            return A2R[i].roman;

    return "";
}

static arabic_t roman_to_arabic(const char *roman) {
    arabic_t arabic = 0;
    arabic_t previous = 0;

    for (size_t i = strlen(roman); i-- > 0;) {
        arabic_t j = roman_digit_to_arabic(roman[i]);

        if (INVALID_ROMAN_NUMERAL == j)
            return INVALID_ROMAN_NUMERAL;

        arabic += (j >= previous) ? j : -j;

        previous = j;
    }

    return arabic;
}

static void not_test_driven_antisocial_process_exit_from_library_call(void) {
    err(EX_OSERR, NULL);
}

static void append_to_roman(char **romanp, const char *roman_value) {
    char *roman = *romanp;
    size_t new_length = strlen(roman) + strlen(roman_value) + NULL_BYTE_LENGTH;

    char *new_roman = realloc(roman, new_length);
    if (new_roman == NULL) {
        free(roman);
        not_test_driven_antisocial_process_exit_from_library_call();
    } else {
        roman = new_roman;
    }

    strcat(roman, roman_value);
}

static char * arabic_to_roman(int arabic) {
    char *roman = malloc(NULL_BYTE_LENGTH);

    if (roman == NULL)
        not_test_driven_antisocial_process_exit_from_library_call();

    *roman = '\0';

    while (arabic > 0) {
        for (size_t i = 0; i < A2R_LENGTH; i++) {
            for (int j = A2R[i].arabic; arabic >= j; ) {
                append_to_roman(&roman, arabic_increment_to_roman(j));
                arabic -= j;
            }
        }
    }

    return roman;
}

static char * normalize_roman(const char *roman) {
    return arabic_to_roman(roman_to_arabic(roman));
}

static bool would_we_ever_construct_that_roman_number(const char *roman) {
    return (0 == strcmp(roman, normalize_roman(roman)));
}

static bool is_valid_roman(const char *roman) {
    return would_we_ever_construct_that_roman_number(roman);
}

static char * roman_operation(char op, const char *roman1, const char *roman2) {
    arabic_t arabic1, arabic2;

    if (!is_valid_roman(roman1) || !is_valid_roman(roman2))
        return "INVALID";

    arabic1 = roman_to_arabic(roman1);
    arabic2 = roman_to_arabic(roman2);

    switch (op) {
        case '+':
            return arabic_to_roman(arabic1 + arabic2);
            break;
        case '-':
            if (arabic1 <= arabic2) {
                return "UNDERFLOW";
            } else {
                return arabic_to_roman(arabic1 - arabic2);
            }
            break;
        default:
            return "";
            break;
    }
}

char * roman_add(const char *roman1, const char *roman2) {
    return roman_operation('+', roman1, roman2);
}

char * roman_subtract(const char *roman1, const char *roman2) {
    return roman_operation('-', roman1, roman2);
}
