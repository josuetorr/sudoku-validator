CC=gcc
FLAGS=-Wall -pedantic -std=c99 -Werror -pthread
# FLAGS=-Wall -pedantic -std=c99 -pthread
SRC=tp1.c sudoku.c
HEADERS=sudoku.h errors_sudoku.h
EXE=sudoku.out

.PHONY: clean default

default: ${EXE}

${EXE}: ${SRC} ${HEADERS}
	${CC} -o ${EXE} ${SRC} ${FLAGS}

clean:
	rm -rf ${EXE} *.o
