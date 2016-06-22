THE_TESTS	=  check_roman_calculator

CFLAGS		+= -Wall -Werror -Wextra -std=c99
TEST_CFLAGS	:= $(shell pkg-config --cflags check)
TEST_LIBS	:= $(shell pkg-config --libs check)

SILENT		= @

check: roman_calculator.a roman_calculator.h check_roman_calculator.c check_roman_calculator_interface.c check_roman_calculator_internals.c
	${SILENT}${CC} ${CFLAGS} ${TEST_CFLAGS} -o ${THE_TESTS} check_roman_calculator_interface.c check_roman_calculator_internals.c check_roman_calculator.c ${TEST_LIBS} roman_calculator.a
	${SILENT}./${THE_TESTS}

romancalc: roman_calculator.a roman_calculator.h romancalc.c
	${SILENT}${CC} ${CFLAGS} -o romancalc romancalc.c roman_calculator.a

roman_calculator.a: roman_calculator.h roman_calculator.c
	${SILENT}${CC} ${CFLAGS} -c roman_calculator.c
	${SILENT}ar rc roman_calculator.a roman_calculator.o
	${SILENT}ranlib roman_calculator.a

clean:
	${SILENT}rm -f ${THE_TESTS} *.a *.o romancalc
