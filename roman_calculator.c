#include <stdlib.h>
#include <string.h>

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

int roman_digit_to_arabic(const char roman_digit) {
    const char as_string[] = { roman_digit, '\0' };

    for (size_t i = 0; i < A2R_LENGTH; i++) {
        if (0 == strcmp(as_string, A2R[i].roman)) {
            return A2R[i].arabic;
        }
    }

    return INVALID_ROMAN_NUMERAL;
}

const char * arabic_increment_to_roman(int arabic_increment) {
    for (size_t i = 0; i < A2R_LENGTH; i++) {
        if (arabic_increment == A2R[i].arabic) {
            return A2R[i].roman;
        }
    }

    return "";
}

int roman_to_arabic(const char *roman) {
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

char * _build_up_roman(char *roman, const char *roman_value) {
    char *newroman = malloc(strlen(roman) + strlen(roman_value));
    strcpy(newroman, roman);
    strcat(newroman, roman_value);
    free(roman);
    return newroman;
}

const char * arabic_to_roman(int arabic) {
    char *roman = malloc(0);

    while (arabic > 0) {
        for (size_t i = 0; i < A2R_LENGTH; i++) {
            for (int j = A2R[i].arabic; arabic >= j; ) {
                roman = _build_up_roman(roman, arabic_increment_to_roman(j));
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
