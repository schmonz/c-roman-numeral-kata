#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "roman_calculator.h"

struct a2r {
    const int arabic;
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

static int roman_digit_to_arabic(const char roman_digit) {
    const char as_string[] = { roman_digit, '\0' };

    for (size_t i = 0; i < A2R_LENGTH; i++)
        if (0 == strcmp(as_string, A2R[i].roman))
            return A2R[i].arabic;

    return INVALID_ROMAN_NUMERAL;
}

static const char * arabic_increment_to_roman(int arabic_increment) {
    for (size_t i = 0; i < A2R_LENGTH; i++)
        if (arabic_increment == A2R[i].arabic)
            return A2R[i].roman;

    return "";
}

static int roman_to_arabic(const char *roman) {
    int arabic = 0;
    int previous_digit_value = 0;

    for (size_t i = strlen(roman); i-- > 0;) {
        int each_digit_value = roman_digit_to_arabic(roman[i]);

        if (each_digit_value == INVALID_ROMAN_NUMERAL) {
            return INVALID_ROMAN_NUMERAL;
        } else if (each_digit_value < previous_digit_value) {
            arabic -= each_digit_value;
        } else {
            arabic += each_digit_value;
        }

        previous_digit_value = each_digit_value;
    }

    return arabic;
}

static void die_on_alloc_failure_even_though_not_test_driven(void) {
    err(EX_OSERR, NULL);
}

static void append_to_roman(char **romanp, const char *roman_value) {
    char *roman = &(**romanp);
    size_t new_length = 1 + strlen(roman) + strlen(roman_value);

    if (NULL == realloc(roman, new_length))
        die_on_alloc_failure_even_though_not_test_driven();

    strlcat(roman, roman_value, new_length);
}

static const char * arabic_to_roman(int arabic) {
    char *roman;

    if (NULL == (roman = malloc(1)))
        die_on_alloc_failure_even_though_not_test_driven();

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

const char * roman_add(const char *roman1, const char *roman2) {
    return arabic_to_roman(roman_to_arabic(roman1) + roman_to_arabic(roman2));
}

const char * roman_subtract(const char *roman1, const char *roman2) {
    return arabic_to_roman(roman_to_arabic(roman1) - roman_to_arabic(roman2));
}
