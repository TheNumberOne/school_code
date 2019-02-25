all: project

project: main.o
	g++ main.o -o project

main.o: main.cpp util.h Person.h LinkedList.h BinaryTree.h
	g++ -std=c++0x -c main.cpp

clean:
	rm *.o project
