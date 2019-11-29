CC=g++ -std=c++0x

all: serializer

serializer: main.o
	$(CC) -o serializer main.o

main.o: main.cpp serializer.h
	$(CC) -c main.cpp

run: serializer
	./serializer

clean:
	rm -rf *.o serializer
