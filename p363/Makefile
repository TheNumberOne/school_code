all: project

project: main.o
	g++ main.o -o project

main.o: main.cpp dynamic.h util.h
	g++ -std=c++0x -c main.cpp

clean:
	rm *.o project
