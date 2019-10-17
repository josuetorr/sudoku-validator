CC=gcc
FLAGS=-Wall -pedantic -std=c99 -Werror -pthread
SRC=tp1.c
EXE=sudoku.out

.PHONY: clean default

default: ${EXE}

${EXE}: ${SRC}
	${CC} -o ${EXE} ${SRC} ${FLAGS}	

clean:
	rm -rf ${EXE} *.o
