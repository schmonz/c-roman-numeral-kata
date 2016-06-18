#include <check.h>

START_TEST(test_roman_numerals_create) {
    ck_assert_msg(1 == 1, "one is not zero");
} END_TEST

Suite * roman_numerals_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Roman Numeral Calculator");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_roman_numerals_create);
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
