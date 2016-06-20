#include <check.h>
#include <stdlib.h>

#define INVALID_ROMAN_NUMERAL -1

const int ARABICS[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
const int ARABICS_LENGTH = sizeof(ARABICS) / sizeof(ARABICS[0]);

/*
 * TODO:
 * push code down from tests to library
 * test more edge cases
 * split tests as helpful
 */

static const int roman_digit_to_arabic(const char roman_digit) {
    switch (roman_digit) {
        case 'M': return 1000;
        case 'D': return  500;
        case 'C': return  100;
        case 'L': return   50;
        case 'X': return   10;
        case 'V': return    5;
        case 'I': return    1;
        default:  return INVALID_ROMAN_NUMERAL;
    }
}

static const char * arabic_increment_to_roman(int arabic_increment) {
    switch (arabic_increment) {
        case 1000:  return  "M";
        case  900:  return "CM";
        case  500:  return  "D";
        case  400:  return "CD";
        case  100:  return  "C";
        case   90:  return "XC";
        case   50:  return  "L";
        case   40:  return "XL";
        case   10:  return  "X";
        case    9:  return "IX";
        case    5:  return  "V";
        case    4:  return "IV";
        case    1:  return  "I";
        default:    return   "";
    }
}

static const int roman_to_arabic(const char *roman) {
    int arabic = 0;
    int previous_digit_value = 0;

    for (int i = strlen(roman) - 1; i >= 0; i--) {
        int this_digit_value = roman_digit_to_arabic(roman[i]);

        if (this_digit_value == INVALID_ROMAN_NUMERAL) {
            return INVALID_ROMAN_NUMERAL;
        } else if (this_digit_value < previous_digit_value) {
            arabic -= this_digit_value;
        } else {
            arabic += this_digit_value;
        }

        previous_digit_value = this_digit_value;
    }

    return arabic;
}

static const char * _build_up_roman(const char *roman, int arabic_increment) {
    const char *roman_value = arabic_increment_to_roman(arabic_increment);
    char *newroman = malloc(strlen(roman) + strlen(roman_value));
    strcpy(newroman, roman);
    strcat(newroman, roman_value);
    free((void *)roman);
    return newroman;
}

static const char * arabic_to_roman(int arabic) {
    const char *roman = malloc(0);

    while (arabic > 0) {
        for (int i = 0; i < ARABICS_LENGTH; i++) {
            int this_arabic = ARABICS[i];
            while (arabic >= this_arabic) {
                roman = _build_up_roman(roman, this_arabic);
                arabic -= this_arabic;
            }
        }
    }

    return roman;
}

static const char * roman_add(const char *roman1, const char *roman2) {
    return arabic_to_roman(roman_to_arabic(roman1) + roman_to_arabic(roman2));
}

static const char * roman_subtract(const char *roman1, const char *roman2) {
    return arabic_to_roman(roman_to_arabic(roman1) - roman_to_arabic(roman2));
}

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
