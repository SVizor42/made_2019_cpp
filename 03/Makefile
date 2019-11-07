CC=g++ -std=c++0x

all: parser

parser: main.o parser.o
	$(CC) -o parser main.o parser.o

main.o: main.cpp parser.h
	$(CC) -c main.cpp

parser.o: parser.cpp parser.h
	$(CC) -c parser.cpp

run: parser
	./parser

clean:
	rm -rf *.o parser
