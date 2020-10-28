CC = -g++ -std=c++17

all: program

program: main.o tests.o 
	$(CC) tests.o main.o -o program

main.o: main.cpp
	$(CC) -c main.cpp

tests.o: tests.cpp tests.h
	$(CC) -c tests.cpp

test: program
	./program

clean:
	rm *.o program