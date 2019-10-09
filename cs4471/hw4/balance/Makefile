all: balancing

balancing: balancing.o
	g++ -std=c++11 balancing.o -o balancing

balancing.o: balancing.cpp
	g++ -std=c++11 -c balancing.cpp

clean:
	rm *o balancing

