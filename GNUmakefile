SILENT		?= @

DEFAULT_SYSTEM	=  host
THE_TESTS	=  check_roman_calculator
THE_LIBRARY	=  roman_calculator.a
THE_PROGRAM	=  romancalc

TARGET_SYSTEM	?= ${DEFAULT_SYSTEM}
ifeq (rpi, ${TARGET_SYSTEM})
MAKE_TARGET	= ${THE_PROGRAM}
NETBSDSRCDIR	?= ${HOME}/Documents/trees/netbsd-src
CROSS_ROOT	?= ${HOME}/rpi
CROSS_ARCH	?= evbearmv6hf-el
CFLAGS		+= --sysroot=${CROSS_ROOT}/distrib/${CROSS_ARCH}
TOOLDIR		?= ${CROSS_ROOT}/tools
TARGET_PREFIX	= armv6--netbsdelf-eabihf-
else
MAKE_TARGET	= check
TOOLDIR		?= /usr
TARGET_PREFIX	?=
endif

CC		= ${TOOLDIR}/bin/${TARGET_PREFIX}gcc
LD		= ${TOOLDIR}/bin/${TARGET_PREFIX}ld
AR		= ${TOOLDIR}/bin/${TARGET_PREFIX}ar
RANLIB		= ${TOOLDIR}/bin/${TARGET_PREFIX}ranlib

CFLAGS		+= -g -O0 -Wall -Werror -Wextra -std=c99
TEST_CFLAGS	:= $(shell pkg-config --cflags check)
TEST_LIBS	:= $(shell pkg-config --libs check)
TEST_LIBS	+= -lm

all:
	${SILENT}${MAKE} ${MAKE_TARGET}

${NETBSDSRCDIR}:
	${SILENT}mkdir -p ${NETBSDSRCDIR} && cd ${NETBSDSRCDIR} && git clone https://github.com/jsonn/src.git .

${CC}: ${NETBSDSRCDIR}
	${SILENT}cd ${NETBSDSRCDIR} && git checkout netbsd_7_0 && env PATH="/usr/local/bin:/opt/pkg/bin:/opt/pkg/sbin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin" MAKECONF="/dev/null" ./build.sh -m ${CROSS_ARCH} -u -U -T ${TOOLDIR} -R ${CROSS_ROOT}/release -O ${CROSS_ROOT}/obj/${CROSS_ARCH} -D ${CROSS_ROOT}/distrib/${CROSS_ARCH} distribution

check: ${THE_TESTS}
	${SILENT}./${THE_TESTS}

valgrind: check ${THE_TESTS} ${THE_PROGRAM}
	${SILENT}valgrind --leak-check=full --error-exitcode=99 ./${THE_TESTS} >/dev/null 2>&1
	${SILENT}valgrind --leak-check=full --error-exitcode=88 ./${THE_PROGRAM} XIV + MCM >/dev/null 2>&1

clean:
	${SILENT}rm -f *.o ${THE_TESTS} ${THE_LIBRARY} ${THE_PROGRAM}
	${SILENT}rm -rf *.dSYM *.gcda *.gcno *.gcov

.PHONY: all check valgrind clean

${THE_TESTS}: ${THE_LIBRARY} check_roman_calculator.c check_roman_calculator_acceptance.c check_roman_calculator_unit.c
	${SILENT}${CC} ${CFLAGS} ${TEST_CFLAGS} -o ${THE_TESTS} check_roman_calculator_acceptance.c check_roman_calculator_unit.c check_roman_calculator.c ${TEST_LIBS} ${THE_LIBRARY}

${THE_LIBRARY}: roman_calculator.h roman_calculator.c
	${SILENT}${CC} ${CFLAGS} -c roman_calculator.c
	${SILENT}${AR} rc ${THE_LIBRARY} roman_calculator.o
	${SILENT}${RANLIB} ${THE_LIBRARY}

${THE_PROGRAM}: ${THE_LIBRARY} roman_calculator.h romancalc.c
	${SILENT}${CC} ${CFLAGS} -o ${THE_PROGRAM} romancalc.c ${THE_LIBRARY}
