#include <check.h>
#include <stdio.h>

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

START_TEST(test_invalid_roman_to_arabic) {
    ck_assert(INVALID_ROMAN_NUMERAL == roman_to_arabic("R"));
    ck_assert(INVALID_ROMAN_NUMERAL == roman_to_arabic("VIIR"));
} END_TEST

START_TEST(test_valid_roman_digits_to_arabic) {
    ck_assert(1 == roman_to_arabic("I"));
    ck_assert(5 == roman_to_arabic("V"));
    ck_assert(10 == roman_to_arabic("X"));
    ck_assert(50 == roman_to_arabic("L"));
    ck_assert(100 == roman_to_arabic("C"));
    ck_assert(500 == roman_to_arabic("D"));
    ck_assert(1000 == roman_to_arabic("M"));
} END_TEST

START_TEST(test_additively_constructed_roman_numerals) {
    ck_assert(2 == roman_to_arabic("II"));
    ck_assert(8 == roman_to_arabic("VIII"));
} END_TEST

START_TEST(test_subtractively_constructed_roman_numerals) {
    ck_assert(4 == roman_to_arabic("IV"));
    ck_assert(1990 == roman_to_arabic("MCMXC"));
    ck_assert(47 == roman_to_arabic("XLVII"));
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
