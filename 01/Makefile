CC = g++ --std=c++17

all: program

program: main.o tests.o allocator.o
	$(CC) tests.o allocator.o main.o -o program


allocator.o: allocator.cpp allocator.h
	$(CC) -c allocator.cpp

tests.o: tests.cpp tests.h
	$(CC) -c tests.cpp

main.o: main.cpp
	$(CC) -c main.cpp


test: program
	./program

clean:
	rm *.o program