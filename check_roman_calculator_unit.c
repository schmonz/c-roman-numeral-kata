#include <check.h>

#include "roman_calculator.c"

START_TEST(test_roman_contains_nonexistent_numerals) {
    ck_assert_str_eq(                   "", normalize_roman("R"));
    ck_assert_int_eq(INVALID_ROMAN_NUMERAL, roman_to_arabic("R"));
    ck_assert_str_eq(                   "", normalize_roman("VIIR"));
    ck_assert_int_eq(INVALID_ROMAN_NUMERAL, roman_to_arabic("VIIR"));
} END_TEST

START_TEST(test_cant_have_more_than_three) {
    ck_assert_str_eq("III", normalize_roman(  "III"));
    ck_assert_str_eq( "IV", normalize_roman( "IIII"));
    ck_assert_str_eq(  "V", normalize_roman("IIIII"));
    ck_assert_str_eq( "XL", normalize_roman( "XXXX"));
    ck_assert_str_eq( "CD", normalize_roman( "CCCC"));
} END_TEST

START_TEST(test_cant_have_more_than_one) {
    ck_assert_str_eq("V", normalize_roman( "V"));
    ck_assert_str_eq("X", normalize_roman("VV"));
    ck_assert_str_eq("C", normalize_roman("LL"));
    ck_assert_str_eq("M", normalize_roman("DD"));
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

TCase* tcase_unit(void) {
    TCase *tc = tcase_create("Unit Tests");

    tcase_add_test(tc, test_roman_contains_nonexistent_numerals);
    tcase_add_test(tc, test_cant_have_more_than_three);
    tcase_add_test(tc, test_cant_have_more_than_one);
    tcase_add_test(tc, test_valid_roman_digits_to_arabic);
    tcase_add_test(tc, test_additively_constructed_roman_numerals);
    tcase_add_test(tc, test_subtractively_constructed_roman_numerals);
    tcase_add_test(tc, test_arabic_to_roman);

    return tc;
}
