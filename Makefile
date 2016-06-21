THE_TESTS	=  check_roman_calculator

CFLAGS		+= -Wall -Werror
TEST_CFLAGS	+= -I /opt/pkg/include
TEST_LDFLAGS	+= -L /opt/pkg/lib
TEST_LIBS	=  -lcheck

SILENT		= @

check: roman_calculator.a roman_calculator.h check_roman_calculator.c check_roman_calculator_interface.c check_roman_calculator_internals.c
	${SILENT}${CC} ${CFLAGS} ${TEST_CFLAGS} ${TEST_LDFLAGS} ${TEST_LIBS} -o ${THE_TESTS} roman_calculator.a check_roman_calculator_interface.c check_roman_calculator_internals.c check_roman_calculator.c
	${SILENT}./${THE_TESTS}

romancalc: roman_calculator.a roman_calculator.h romancalc.c
	${SILENT}${CC} ${CFLAGS} -o romancalc roman_calculator.a romancalc.c

roman_calculator.a: roman_calculator.h roman_calculator.c
	${SILENT}${CC} ${CFLAGS} -c roman_calculator.c
	${SILENT}ar rc roman_calculator.a roman_calculator.o
	${SILENT}ranlib roman_calculator.a

clean:
	${SILENT}rm -f ${THE_TESTS} *.a *.o romancalc
