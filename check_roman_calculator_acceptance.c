#include <check.h>

#include "roman_calculator.h"

START_TEST(test_add_invalid_roman_numbers) {
    ck_assert_str_eq("INVALID", roman_add("V", "R"));
    ck_assert_str_eq("INVALID", roman_add("ORIOLE", "V"));
    ck_assert_str_eq("INVALID", roman_add("R", "R"));
    ck_assert_str_eq("INVALID", roman_add("VIIII", "V"));
} END_TEST

START_TEST(test_add_two_roman_numbers) {
    ck_assert_str_eq("LXXIV", roman_add("XIV", "LX"));
    ck_assert_str_eq( "XXII", roman_add( "XX", "II"));
} END_TEST

START_TEST(test_subtract_two_roman_numbers) {
    ck_assert_str_eq("XLVI", roman_subtract("LX", "XIV"));
} END_TEST

TCase* tcase_acceptance(void) {
    TCase *tc = tcase_create("Acceptance Tests");

    tcase_add_test(tc, test_add_invalid_roman_numbers);
    tcase_add_test(tc, test_add_two_roman_numbers);
    tcase_add_test(tc, test_subtract_two_roman_numbers);

    return tc;
}
