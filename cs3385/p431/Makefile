all: project

project: main.o huffman.o
	g++ main.o huffman.o -o project

main.o: main.cpp huffman.h util.h
	g++ -std=c++0x -c main.cpp

huffman.o: huffman.cpp huffman.h
	g++ -std=c++0x -c huffman.cpp

clean:
	rm *.o project
