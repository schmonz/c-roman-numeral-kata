#include <check.h>

TCase* tcase_unit(void);
TCase* tcase_acceptance(void);

Suite * roman_numerals_suite(void) {
    Suite *s = suite_create("Roman Numeral Calculator");

    suite_add_tcase(s, tcase_unit());
    suite_add_tcase(s, tcase_acceptance());

    return s;
}

int main(void) {
    int number_failed;
    SRunner *sr = srunner_create(roman_numerals_suite());
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed;
}
