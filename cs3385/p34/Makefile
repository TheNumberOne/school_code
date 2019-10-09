all: project

project: main.o MergeSort.o
	g++ main.o MergeSort.o -o project

main.o: main.cpp
	g++ -c main.cpp

MergeSort.o: MergeSort.cpp MergeSort.h
	g++ -c MergeSort.cpp

clean:
	rm *.o project
