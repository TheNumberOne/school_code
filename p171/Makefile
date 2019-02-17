all: project

project: main.o
	g++ main.o -o project

main.o: main.cpp Person.h Song.h insertion.h bubble.h quicksort.h
	g++ -c main.cpp

clean:
	rm *.o project
