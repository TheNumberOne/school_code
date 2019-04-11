all: deadlock

deadlock: deadlock.o
	g++ -std=c++11 deadlock.o -o deadlock

deadlock.o: deadlock.cpp
	g++ -std=c++11 -c deadlock.cpp

clean:
	rm *o deadlock

