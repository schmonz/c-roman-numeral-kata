THE_TESTS =	the_tests

CFLAGS +=	-Wall -Werror
CFLAGS +=	-I /opt/pkg/include
LDFLAGS +=	-L /opt/pkg/lib
LIBS =		-lcheck

SILENT =	@

check: check_roman_numeral_calculator.c
	${SILENT}${CC} ${CFLAGS} ${LDFLAGS} ${LIBS} -o ${THE_TESTS} check_roman_numeral_calculator.c
	${SILENT}./${THE_TESTS}

clean:
	${SILENT}rm -f ${THE_TESTS}
