CC=g++ -std=c++0x

all: vector

vector: main.o
	$(CC) -o vector main.o

main.o: main.cpp vector.h
	$(CC) -c main.cpp

run: vector
	./vector

clean:
	rm -rf *.o vector
