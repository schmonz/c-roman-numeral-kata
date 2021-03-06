#include <check.h>

#include <stdlib.h>

#include "roman_calculator.c"

static void check_normalize(const char *expected, const char *input) {
    char* actual = normalize_roman(input);
    ck_assert_str_eq(expected, actual);
    free(actual);
}

static void check_arabic_to_roman(const char *expected, int input) {
    char *actual = arabic_to_roman(input);
    ck_assert_str_eq(expected, actual);
    free(actual);
}

START_TEST(test_roman_contains_nonexistent_numerals) {
    check_normalize("", "R");
    ck_assert_int_eq(INVALID_ROMAN_NUMERAL, roman_to_arabic("R"));
    check_normalize("", "VIIR");
    ck_assert_int_eq(INVALID_ROMAN_NUMERAL, roman_to_arabic("VIIR"));
} END_TEST

START_TEST(test_cant_have_more_than_three) {
    check_normalize("III",   "III");
    check_normalize( "IV",  "IIII");
    check_normalize(  "V", "IIIII");
    check_normalize( "XL",  "XXXX");
    check_normalize( "CD",  "CCCC");
} END_TEST

START_TEST(test_cant_have_more_than_one) {
    check_normalize("V",  "V");
    check_normalize("X", "VV");
    check_normalize("C", "LL");
    check_normalize("M", "DD");
} END_TEST

START_TEST(test_document_behavior_on_other_malformed_roman_input) {
    check_normalize(     "V",          "IIV");
    check_normalize("CMXCIX",           "IM");
    check_normalize(     "M",          "IIM");
    check_normalize(    "MI",         "IIIM");
    check_normalize(   "MII",        "IIIIM");
    check_normalize(  "MIII",       "IIIIIM");
    check_normalize(  "MXXI", "IVIVVIVIVIIM");
    check_normalize(   "CML",           "LM");
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

START_TEST(test_nonexistent_arabic_increment) {
    ck_assert_str_eq("ERROR_NO_ROMAN_INCREMENT", arabic_increment_to_roman(47));
} END_TEST

START_TEST(test_arabic_to_roman) {
    check_arabic_to_roman(      "I",    1);
    check_arabic_to_roman(     "VI",    6);
    check_arabic_to_roman(     "IV",    4);
    check_arabic_to_roman(     "IX",    9);
    check_arabic_to_roman(   "XXII",   22);
    check_arabic_to_roman(  "LXXIV",   74);
    check_arabic_to_roman("MCMXCIX", 1999);
} END_TEST

START_TEST(test_nonexistent_roman_operation) {
    ck_assert_str_eq("ERROR_NO_ROMAN_OPERATOR", roman_operation('&', "V", "I"));
} END_TEST

TCase* tcase_unit(void) {
    TCase *tc = tcase_create("Unit Tests");

    tcase_add_test(tc, test_roman_contains_nonexistent_numerals);
    tcase_add_test(tc, test_cant_have_more_than_three);
    tcase_add_test(tc, test_cant_have_more_than_one);
    tcase_add_test(tc, test_document_behavior_on_other_malformed_roman_input);
    tcase_add_test(tc, test_valid_roman_digits_to_arabic);
    tcase_add_test(tc, test_additively_constructed_roman_numerals);
    tcase_add_test(tc, test_subtractively_constructed_roman_numerals);
    tcase_add_test(tc, test_nonexistent_arabic_increment);
    tcase_add_test(tc, test_arabic_to_roman);
    tcase_add_test(tc, test_nonexistent_roman_operation);

    return tc;
}
