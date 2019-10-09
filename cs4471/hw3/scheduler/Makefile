all: scheduler

scheduler: scheduler.o
	g++ -std=c++11 scheduler.o -o scheduler

scheduler.o: scheduler.cpp
	g++ -std=c++11 -c scheduler.cpp

clean:
	rm *o scheduler

