CC = g++ --std=c++17

all: program

program: allocator.o
	$(CC) allocator.o -o program

allocator.o: allocator.cpp allocator.h
	$(CC) -c my_allocator.cpp

test: program
	./program

clean:
	rm *.o program