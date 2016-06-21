#include <check.h>

#include "roman_calculator.h"

/*
 * TODO:
 * split tests better
 * test more edge cases
 * reduce more duplication
 * try on Ubuntu with gcc, fixing whatever breaks
 * submit!
 */

START_TEST(test_invalid_roman_to_arabic) {
    ck_assert_int_eq(INVALID_ROMAN_NUMERAL, roman_to_arabic("R"));
    ck_assert_int_eq(INVALID_ROMAN_NUMERAL, roman_to_arabic("VIIR"));
} END_TEST

START_TEST(test_valid_roman_digits_to_arabic) {
    ck_assert_int_eq(   1, roman_to_arabic(    "I"));
    ck_assert_int_eq(   5, roman_to_arabic(    "V"));
    ck_assert_int_eq(  10, roman_to_arabic(    "X"));
    ck_assert_int_eq(  50, roman_to_arabic(    "L"));
    ck_assert_int_eq( 100, roman_to_arabic(    "C"));
    ck_assert_int_eq( 500, roman_to_arabic(    "D"));
    ck_assert_int_eq(1000, roman_to_arabic(    "M"));
} END_TEST

START_TEST(test_additively_constructed_roman_numerals) {
    ck_assert_int_eq(   2, roman_to_arabic(   "II"));
    ck_assert_int_eq(   8, roman_to_arabic( "VIII"));
} END_TEST

START_TEST(test_subtractively_constructed_roman_numerals) {
    ck_assert_int_eq(   4, roman_to_arabic(   "IV"));
    ck_assert_int_eq(1990, roman_to_arabic("MCMXC"));
    ck_assert_int_eq(  47, roman_to_arabic("XLVII"));
} END_TEST

START_TEST(test_arabic_to_roman) {
    ck_assert_str_eq(arabic_to_roman(   1),       "I");
    ck_assert_str_eq(arabic_to_roman(   6),      "VI");
    ck_assert_str_eq(arabic_to_roman(   4),      "IV");
    ck_assert_str_eq(arabic_to_roman(   9),      "IX");
    ck_assert_str_eq(arabic_to_roman(  22),    "XXII");
    ck_assert_str_eq(arabic_to_roman(  74),   "LXXIV");
    ck_assert_str_eq(arabic_to_roman(1999), "MCMXCIX");
} END_TEST

START_TEST(test_add_two_roman_numerals) {
    ck_assert_str_eq("LXXIV", roman_add("XIV", "LX"));
    ck_assert_str_eq( "XXII", roman_add( "XX", "II"));
} END_TEST

START_TEST(test_subtract_two_roman_numerals) {
    ck_assert_str_eq("XLVI", roman_subtract("LX", "XIV"));
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
    tcase_add_test(tc_core, test_arabic_to_roman);
    tcase_add_test(tc_core, test_add_two_roman_numerals);
    tcase_add_test(tc_core, test_subtract_two_roman_numerals);
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
