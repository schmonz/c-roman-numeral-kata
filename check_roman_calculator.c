#include <check.h>

TCase* tcase_interface(void);
TCase* tcase_internals(void);

Suite * roman_numerals_suite(void) {
    Suite *s = suite_create("Roman Numeral Calculator");

    suite_add_tcase(s, tcase_interface());
    suite_add_tcase(s, tcase_internals());

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
