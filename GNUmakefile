THE_TESTS	=  check_roman_calculator
THE_LIBRARY	=  roman_calculator.a
THE_PROGRAM	=  romancalc

CFLAGS		+= -g -O0 -Wall -Werror -Wextra -std=c99
TEST_CFLAGS	:= $(shell pkg-config --cflags check)
TEST_LIBS	:= $(shell pkg-config --libs check)
TEST_LIBS	+= -lm

SILENT		=  @

all: check

check: ${THE_TESTS}
	${SILENT}./${THE_TESTS}

valgrind: check ${THE_TESTS} ${THE_PROGRAM}
	${SILENT}valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=99 ./${THE_TESTS}
	${SILENT}valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=88 ./${THE_PROGRAM} XIV + MCM

clean:
	${SILENT}rm -f *.o ${THE_TESTS} ${THE_LIBRARY} ${THE_PROGRAM}
	${SILENT}rm -rf *.dSYM

.PHONY: all check valgrind clean

${THE_TESTS}: ${THE_LIBRARY} check_roman_calculator.c check_roman_calculator_acceptance.c check_roman_calculator_unit.c
	${SILENT}${CC} ${CFLAGS} ${TEST_CFLAGS} -o ${THE_TESTS} check_roman_calculator_acceptance.c check_roman_calculator_unit.c check_roman_calculator.c ${TEST_LIBS} ${THE_LIBRARY}

${THE_LIBRARY}: roman_calculator.h roman_calculator.c
	${SILENT}${CC} ${CFLAGS} -c roman_calculator.c
	${SILENT}ar rc ${THE_LIBRARY} roman_calculator.o
	${SILENT}ranlib ${THE_LIBRARY}

${THE_PROGRAM}: ${THE_LIBRARY} roman_calculator.h romancalc.c
	${SILENT}${CC} ${CFLAGS} -o ${THE_PROGRAM} romancalc.c ${THE_LIBRARY}
