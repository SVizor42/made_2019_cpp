CC=g++ 
FLAGS=-std=c++0x -pthread

all: threadpool

threadpool: main.o threadpool.o
	$(CC) $(FLAGS) -o threadpool main.o threadpool.o

main.o: main.cpp threadpool.h
	$(CC) $(FLAGS) -c main.cpp

threadpool.o: threadpool.cpp threadpool.h
	$(CC) $(FLAGS) -c threadpool.cpp

run: threadpool
	./threadpool

clean:
	rm -rf *.o threadpool
