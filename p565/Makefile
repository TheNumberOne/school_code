all: project

project: main.o DisjointSet.o bmp.o
	$(CXX) main.o DisjointSet.o bmp.o -o project

main.o: main.cpp DisjointSet.h bmp.h util.h Color.h
	$(CXX) -std=c++0x -c main.cpp

bmp.o: bmp.cpp bmp.h
	$(CXX) -std=c++0x -c bmp.cpp

DisjointSet.o: DisjointSet.cpp DisjointSet.h
	$(CXX) -std=c++0x -c DisjointSet.cpp

clean:
	rm *.o project
