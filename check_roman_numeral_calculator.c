#include <check.h>
#include <stdlib.h>

#define INVALID_ROMAN_NUMERAL -1

static int roman_digit_to_arabic(const char *roman_digit) {
    if (0 == strcmp(roman_digit, "M"))
        return 1000;
    if (0 == strcmp(roman_digit, "D"))
        return 500;
    if (0 == strcmp(roman_digit, "C"))
        return 100;
    if (0 == strcmp(roman_digit, "L"))
        return 50;
    if (0 == strcmp(roman_digit, "X"))
        return 10;
    if (0 == strcmp(roman_digit, "V"))
        return 5;
    if (0 == strcmp(roman_digit, "I"))
        return 1;

    return INVALID_ROMAN_NUMERAL;
}

static int roman_to_arabic(const char *roman) {
    int arabic = 0;
    int previous_digit_value = 0;

    for (int i = strlen(roman) - 1; i >= 0; i--) {
        int this_digit_value;
        char roman_digit[2];

        strncpy(roman_digit, roman+i, 1);
        roman_digit[1] = '\0';

        this_digit_value = roman_digit_to_arabic(roman_digit);

        if (this_digit_value == INVALID_ROMAN_NUMERAL) {
            return INVALID_ROMAN_NUMERAL;
        } else if (this_digit_value < previous_digit_value) {
            arabic -= this_digit_value;
        } else {
            arabic += this_digit_value;
        }

        previous_digit_value = this_digit_value;
    }

    return arabic;
}

static char * _build_up_roman(char *roman, int increment, char *roman_value) {
        char *newroman = malloc(strlen(roman) + strlen(roman_value));
        strcpy(newroman, roman);
        strcat(newroman, roman_value);
        free(roman);
        return newroman;
}

static const char * arabic_to_roman(int arabic) {
    char *roman = malloc(0);

    while (arabic > 0) {
        if (arabic >= 10) {
            roman = _build_up_roman(roman, 10, "X");
            arabic -= 10;
        } else if (arabic >= 9) {
            roman = _build_up_roman(roman, 9, "IX");
            arabic -= 9;
        } else if (arabic >= 5) {
            roman = _build_up_roman(roman, 5, "V");
            arabic -= 5;
        } else if (arabic >= 4) {
            roman = _build_up_roman(roman, 4, "IV");
            arabic -= 4;
        } else if (arabic >= 1) {
            roman = _build_up_roman(roman, 1, "I");
            arabic -= 1;
        }
    }

    return roman;
}

/*
static int roman_add_to_arabic(const char *roman1, const char *roman2) {
    return roman_to_arabic(roman1) + roman_to_arabic(roman2);
}

static const char * roman_add(const char *roman1, const char *roman2) {
    return arabic_to_roman(roman_add_to_arabic(roman1, roman2));
}
*/

START_TEST(test_invalid_roman_to_arabic) {
    ck_assert_int_eq(INVALID_ROMAN_NUMERAL, roman_to_arabic("R"));
    ck_assert_int_eq(INVALID_ROMAN_NUMERAL, roman_to_arabic("VIIR"));
} END_TEST

START_TEST(test_valid_roman_digits_to_arabic) {
    ck_assert_int_eq(1, roman_to_arabic("I"));
    ck_assert_int_eq(5, roman_to_arabic("V"));
    ck_assert_int_eq(10, roman_to_arabic("X"));
    ck_assert_int_eq(50, roman_to_arabic("L"));
    ck_assert_int_eq(100, roman_to_arabic("C"));
    ck_assert_int_eq(500, roman_to_arabic("D"));
    ck_assert_int_eq(1000, roman_to_arabic("M"));
} END_TEST

START_TEST(test_additively_constructed_roman_numerals) {
    ck_assert_int_eq(2, roman_to_arabic("II"));
    ck_assert_int_eq(8, roman_to_arabic("VIII"));
} END_TEST

START_TEST(test_subtractively_constructed_roman_numerals) {
    ck_assert_int_eq(4, roman_to_arabic("IV"));
    ck_assert_int_eq(1990, roman_to_arabic("MCMXC"));
    ck_assert_int_eq(47, roman_to_arabic("XLVII"));
} END_TEST

START_TEST(test_arabic_to_roman) {
    ck_assert_str_eq(arabic_to_roman(1), "I");
    ck_assert_str_eq(arabic_to_roman(6), "VI");
    ck_assert_str_eq(arabic_to_roman(4), "IV");
    ck_assert_str_eq(arabic_to_roman(9), "IX");
    //ck_assert_str_eq(arabic_to_roman(1999), "MCMXCIX");
} END_TEST

START_TEST(test_add_two_roman_numerals) {
/*
    ck_assert("LXXIV" == roman_add("XIV", "LX"));
    ck_assert("XXII" == roman_add("XX", "II"));
*/
} END_TEST

Suite * roman_numerals_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Roman Numeral Calculator");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_invalid_roman_to_arabic);
    tcase_add_test(tc_core, test_valid_roman_digits_to_arabic);
    tcase_add_test(tc_core, test_additively_constructed_roman_numerals);
    tcase_add_test(tc_core, test_subtractively_constructed_roman_numerals);
    tcase_add_test(tc_core, test_add_two_roman_numerals);
    tcase_add_test(tc_core, test_arabic_to_roman);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    SRunner *sr;

    sr = srunner_create(roman_numerals_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed;
}
