CC = --std=c++17
main: main.o
	g++ main.o -o main $(CC)
main.o: main.cpp
	g++ -c main.cpp $(CC)
format.o: format.h
	g++ -c format.h $(CC)
clean:
	rm *.o
test:
	./main
