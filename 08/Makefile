main: main.o
	g++ main.o -o main -pthread --std=c++17
main.o: main.cpp pthread.cpp tests.cpp
	g++ -c main.cpp --std=c++17
clean:
	rm *.o
test:
	./main
