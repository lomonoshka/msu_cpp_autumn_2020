CC = -g++ -std=c++17

all: program

program: main.o tests.o parser.o
	$(CC) tests.o parser.o main.o -o program


parser.o: parser.cpp parser.h
	$(CC) -c parser.cpp

tests.o: tests.cpp tests.h
	$(CC) -c tests.cpp

main.o: main.cpp
	$(CC) -c main.cpp


test: program
	./program

clean:
	rm *.o program