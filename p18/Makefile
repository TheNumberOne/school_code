all: project

project: main.o InsertionSort.o
	g++ main.o InsertionSort.o -o project

main.o: main.cpp
	g++ -c main.cpp

InsertionSort.o: InsertionSort.cpp InsertionSort.h
	g++ -c InsertionSort.cpp

clean:
	rm *.o project
