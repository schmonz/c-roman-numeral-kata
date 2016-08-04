#include <err.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "roman_calculator.h"

#define STRING_TERMINATOR_LENGTH 1

struct arabic_roman_pair {
    const arabic_t arabic;
    const char *roman;
};

const struct arabic_roman_pair PAIRS[] = {
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
const size_t PAIRS_LENGTH = sizeof(PAIRS) / sizeof(PAIRS[0]);

struct memory_functions {
    void *(*malloc)(size_t size);
    void *(*realloc)(void *pointer, size_t size);
    void (*free)(void *pointer);
};

static struct memory_functions my_memory = {
    malloc,
    realloc,
    free,
};

void set_malloc(void *another_malloc, void *another_free) {
    my_memory.malloc = another_malloc;
    my_memory.free = another_free;
}

void set_realloc(void *another_realloc, void *another_free) {
    my_memory.realloc = another_realloc;
    my_memory.free = another_free;
}

static arabic_t roman_digit_to_arabic(const char roman_digit) {
    const char as_string[] = { roman_digit, '\0' };

    for (size_t i = 0; i < PAIRS_LENGTH; i++)
        if (0 == strcmp(as_string, PAIRS[i].roman))
            return PAIRS[i].arabic;

    return INVALID_ROMAN_NUMERAL;
}

static const char * arabic_increment_to_roman(arabic_t arabic_increment) {
    for (size_t i = 0; i < PAIRS_LENGTH; i++)
        if (arabic_increment == PAIRS[i].arabic)
            return PAIRS[i].roman;

    return "ERROR_NO_ROMAN_INCREMENT";
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

static char * append_to_roman(char *roman, const char *roman_value) {
    size_t new_length = strlen(roman) + strlen(roman_value)
        + STRING_TERMINATOR_LENGTH;

    char *new_roman = my_memory.realloc(roman, new_length);
    if (new_roman == NULL) {
        my_memory.free(roman);
        return "ERROR_NO_REALLOC";
    } else {
        roman = new_roman;
        strcat(roman, roman_value);
    }

    return roman;
}

static char * arabic_to_roman(int arabic) {
    char *roman = my_memory.malloc(STRING_TERMINATOR_LENGTH);

    if (roman == NULL)
        return "ERROR_NO_MALLOC";

    strcpy(roman, "");

    for (size_t i = 0; i < PAIRS_LENGTH; i++) {
        for (int j = PAIRS[i].arabic; arabic >= j; arabic -= j) {
            roman = append_to_roman(roman, arabic_increment_to_roman(j));
        }
    }

    return roman;
}

static char * normalize_roman(const char *roman) {
    return arabic_to_roman(roman_to_arabic(roman));
}

static bool would_we_ever_construct_that_roman_number(const char *roman) {
    bool would_we;
    char *normalized_roman = normalize_roman(roman);

    would_we = (0 == strcmp(roman, normalized_roman));

    my_memory.free(normalized_roman);
    return would_we;
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
            return "ERROR_NO_ROMAN_OPERATOR";
            break;
    }
}

char * roman_add(const char *roman1, const char *roman2) {
    return roman_operation('+', roman1, roman2);
}

char * roman_subtract(const char *roman1, const char *roman2) {
    return roman_operation('-', roman1, roman2);
}
