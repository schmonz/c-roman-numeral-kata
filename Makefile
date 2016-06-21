THE_TESTS	=  the_tests

CFLAGS		+= -Wall -Werror
TEST_CFLAGS	+= -I /opt/pkg/include
TEST_LDFLAGS	+= -L /opt/pkg/lib
TEST_LIBS	=  -lcheck

SILENT		= @

check: roman_calculator.a check_roman_numeral_calculator.c
	${SILENT}${CC} ${CFLAGS} ${TEST_CFLAGS} ${TEST_LDFLAGS} ${TEST_LIBS} -o ${THE_TESTS} roman_calculator.a check_roman_numeral_calculator.c
	${SILENT}./${THE_TESTS}

roman_add: roman_calculator.a roman_calculator.h roman_add.c
	${SILENT}${CC} ${CFLAGS} -o roman_add roman_calculator.a roman_add.c

roman_calculator.a: roman_calculator.h roman_calculator.c
	${SILENT}${CC} ${CFLAGS} -c roman_calculator.c
	${SILENT}ar rc roman_calculator.a roman_calculator.o
	${SILENT}ranlib roman_calculator.a

clean:
	${SILENT}rm -f ${THE_TESTS} *.a *.o roman_add
