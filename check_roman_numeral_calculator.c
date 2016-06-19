#include <check.h>

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
    return roman_digit_to_arabic(roman);
}

START_TEST(test_roman_to_arabic) {
    ck_assert(INVALID_ROMAN_NUMERAL == roman_to_arabic("R"));
    ck_assert(1 == roman_to_arabic("I"));
    ck_assert(5 == roman_to_arabic("V"));
    ck_assert(10 == roman_to_arabic("X"));
    ck_assert(50 == roman_to_arabic("L"));
    ck_assert(100 == roman_to_arabic("C"));
    ck_assert(500 == roman_to_arabic("D"));
    ck_assert(1000 == roman_to_arabic("M"));
} END_TEST

Suite * roman_numerals_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Roman Numeral Calculator");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_roman_to_arabic);
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
