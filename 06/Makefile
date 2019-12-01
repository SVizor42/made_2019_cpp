CC=g++ -std=c++0x

all: big_int

big_int: main.o big_int.o
	$(CC) -o big_int main.o big_int.o

main.o: main.cpp big_int.h
	$(CC) -c main.cpp

big_int.o: big_int.cpp big_int.h
	$(CC) -c big_int.cpp

run: big_int
	./big_int

clean:
	rm -rf *.o big_int
