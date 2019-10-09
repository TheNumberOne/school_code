all: stega

stega: stega.o
	g++ -std=c++11 stega.o -o stega

stega.o: stega.cpp
	g++ -std=c++11 -c stega.cpp

clean:
	rm *o stega

