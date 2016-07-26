#include <check.h>

#include <math.h>
#include <stdlib.h>

#include "roman_calculator.h"

static void check_roman_add(const char *expected, const char *one, const char *two) {
    char *actual = roman_add(one, two);
    ck_assert_str_eq(expected, actual);
    free(actual);
}

static void check_roman_subtract(const char *expected, const char *one, const char *two) {
    char *actual = roman_subtract(one, two);
    ck_assert_str_eq(expected, actual);
    free(actual);
}

START_TEST(test_add_invalid_roman_numbers) {
    ck_assert_str_eq("INVALID", roman_add("V", "R"));
    ck_assert_str_eq("INVALID", roman_add("ORIOLE", "V"));
    ck_assert_str_eq("INVALID", roman_add("R", "R"));
    ck_assert_str_eq("INVALID", roman_add("VIIII", "V"));
} END_TEST

START_TEST(test_add_roman_no_such_thing_as_roman_overflow) {
    check_roman_add("MMMMMMMMMMM", "MMMMM", "MMMMMM");
} END_TEST

START_TEST(test_yes_such_thing_as_c_overflow_and_underflow) {
    const int EXPECTED_ARABIC_T_SIZE = 4;
    const arabic_t ARABIC_MAX = -1 + pow(2, 8 * EXPECTED_ARABIC_T_SIZE);
    const arabic_t ARABIC_MIN = 0;
    arabic_t thingy = ARABIC_MAX;

    ck_assert_int_eq(EXPECTED_ARABIC_T_SIZE, sizeof(arabic_t));

    ++thingy;
    ck_assert_int_eq(thingy, ARABIC_MIN);

    --thingy;
    ck_assert_int_eq(thingy, ARABIC_MAX);

    thingy += 2;
    ck_assert_int_eq(thingy, ARABIC_MIN + 1);
} END_TEST

START_TEST(test_add_two_roman_numbers) {
    check_roman_add("LXXIV", "XIV", "LX");
    check_roman_add( "XXII",  "XX", "II");
} END_TEST

START_TEST(test_subtract_invalid_roman_numbers) {
    ck_assert_str_eq("INVALID", roman_subtract("WEIRDO", "X"));
} END_TEST

START_TEST(test_subtract_roman_underflow) {
    ck_assert_str_eq("UNDERFLOW", roman_subtract("V", "X"));
    ck_assert_str_eq("UNDERFLOW", roman_subtract("X", "X"));
} END_TEST

START_TEST(test_subtract_two_roman_numbers) {
    check_roman_subtract("XLVI", "LX", "XIV");
} END_TEST

TCase* tcase_acceptance(void) {
    TCase *tc = tcase_create("Acceptance Tests");

    tcase_add_test(tc, test_add_invalid_roman_numbers);
    tcase_add_test(tc, test_add_roman_no_such_thing_as_roman_overflow);
    tcase_add_test(tc, test_yes_such_thing_as_c_overflow_and_underflow);
    tcase_add_test(tc, test_add_two_roman_numbers);
    tcase_add_test(tc, test_subtract_invalid_roman_numbers);
    tcase_add_test(tc, test_subtract_roman_underflow);
    tcase_add_test(tc, test_subtract_two_roman_numbers);

    return tc;
}
