CC=g++ -std=c++0x

all: alloc

alloc: main.o alloc.o
	$(CC) -o alloc main.o alloc.o

main.o: main.cpp alloc.h
	$(CC) -c main.cpp

alloc.o: alloc.cpp alloc.h
	$(CC) -c alloc.cpp

run: alloc
	./alloc

clean:
	rm -rf *.o alloc
