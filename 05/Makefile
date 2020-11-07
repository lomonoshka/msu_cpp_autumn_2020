CC = g++ -std=c++17

main: main.o Serializer.o
	$(CC) main.o -o main

main.o: main.cpp
	$(CC) -c main.cpp

Serializer.o: Serializer.cpp Serializer.h
	$(CC) -c Serializer.cpp

Deserializer.o: Deserializer.cpp Deserializer.h
	$(CC) -c Deserializer.cpp
	
clean:
	rm *.o
test:
	./main
