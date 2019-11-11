CC=g++ -std=c++0x

all: matrix

matrix: main.o matrix.o
	$(CC) -o matrix main.o matrix.o

main.o: main.cpp matrix.h
	$(CC) -c main.cpp

matrix.o: matrix.cpp matrix.h
	$(CC) -c matrix.cpp

run: matrix
	./matrix

clean:
	rm -rf *.o matrix
