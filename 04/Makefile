CC = g++ -std=c++17

main: main.o Bigint.o tests.o
	$(CC) main.o Bigint.o tests.o -o main 

main.o: main.cpp
	$(CC) -c main.cpp 

Bigint.o: Bigint.cpp Bigint.h
	$(CC) -c Bigint.cpp 

tests.o: tests.cpp tests.h
	$(CC) -c tests.cpp

clean:
	rm *.o

test:
	./main
