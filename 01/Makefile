CC=g++

all: calc

calc: main.o calc.o
	$(CC) -o calc main.o calc.o

main.o: main.cpp calc.h
	$(CC) -c main.cpp

calc.o: calc.cpp calc.h
	$(CC) -c calc.cpp

run: calc
	./calc "$(ARGS)"

test: test.o calc.o
	$(CC) -o test.out test.o calc.o
	./test.out

test.o: test.cpp calc.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o calc test.out
