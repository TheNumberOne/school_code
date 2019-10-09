all: project

project: main.o Heap.o
	g++ main.o Heap.o -o project

main.o: main.cpp Heap.h
	g++ -c main.cpp

Heap.o: Heap.cpp Heap.h
	g++ -c Heap.cpp

clean:
	rm *.o project
