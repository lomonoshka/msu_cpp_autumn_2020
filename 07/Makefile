CC = --std=c++17
main: main.o
	g++ main.o -o main $(CC)
main.o: main.cpp vector.hpp iterator.hpp allocator.hpp
	g++ -c main.cpp $(CC)
clean:
	rm *.o
test:
	valgrind ./main