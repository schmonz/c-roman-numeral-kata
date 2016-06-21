#ifndef ROMAN_CALCULATOR_H
#define ROMAN_CALCULATOR_H

#define INVALID_ROMAN_NUMERAL -1

const int    roman_digit_to_arabic(const char);
const char * arabic_increment_to_roman(int);
const int    roman_to_arabic(const char *);
const char * _build_up_roman(const char *, int);
const char * arabic_to_roman(int);

const char * roman_add(const char *, const char *);
const char * roman_subtract(const char *, const char *);

#endif
