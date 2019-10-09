all: project

project: main.o
	$(CXX) main.o -o project

main.o: main.cpp util.h hash.h Person.h LinkedList.h HashTable.h
	$(CXX) -std=c++0x -c main.cpp

clean:
	rm *.o project
