#include <check.h>

#include "roman_calculator.h"

START_TEST(test_add_two_roman_numerals) {
    ck_assert_str_eq("LXXIV", roman_add("XIV", "LX"));
    ck_assert_str_eq( "XXII", roman_add( "XX", "II"));
} END_TEST

START_TEST(test_subtract_two_roman_numerals) {
    ck_assert_str_eq("XLVI", roman_subtract("LX", "XIV"));
} END_TEST

TCase* tcase_interface(void) {
    TCase *tc = tcase_create("Interface");

    tcase_add_test(tc, test_add_two_roman_numerals);
    tcase_add_test(tc, test_subtract_two_roman_numerals);

    return tc;
}
