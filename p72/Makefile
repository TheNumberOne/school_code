all: project

project: main.o MaxSubarray.o
	g++ main.o MaxSubarray.o -o project

main.o: main.cpp
	g++ -c main.cpp

MaxSubarray.o: MaxSubarray.cpp MaxSubarray.h
	g++ -c MaxSubarray.cpp

clean:
	rm *.o project
