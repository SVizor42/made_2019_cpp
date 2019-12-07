CC=g++ -std=c++0x

all: format

format: main.o
	$(CC) -o format main.o

main.o: main.cpp format.h
	$(CC) -c main.cpp

run: format
	./format

clean:
	rm -rf *.o format
