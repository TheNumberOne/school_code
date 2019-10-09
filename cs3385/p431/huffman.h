#pragma once

#include <iostream>
#include <string>
#include <queue>

#include "./bit_buffer.h"

using std::string;
using std::vector;
using std::priority_queue;

/**
 * Represents a node in a binary tree
 */
template<typename T>
class BNode
{
public:
    explicit BNode(int key, T value) : _data(value), _left(nullptr), _right(nullptr), _key(key) { }
    
    const T &data() const { return _data; }
    
    T &data() { return _data; }
    
    void data(T data) { _data = data; }
    
    BNode<T> *left() const noexcept { return _left; }
    
    void left(BNode<T> *left) noexcept { _left = left; }
    
    BNode<T> *right() const noexcept { return _right; }
    
    void right(BNode<T> *right) noexcept { _right = right; }
    
    int key() const { return _key; }
    
    void key(int frequency) { _key = frequency; }

private:
    int _key;
    T _data;
    BNode<T> *_left;
    BNode<T> *_right;
};

// Put your BNode class from your BinarySearchTree project above
// this, then comment-out the following line. You can then refer
// to BNode<char> as simply Node.
typedef BNode<char> Node;

// This class will allow us to use the stl priority_queue.
class NodeComp
{
public:
    bool operator()(Node *a, Node *b)
    {
        return a->key() > b->key();
    }
};

struct CharFreq
{
    char c;
    int f;
    
    CharFreq(char c_, int f_) : c(c_), f(f_) { }
};

// Returns the root of the tree
Node *buildBinaryTree(const vector<CharFreq> &chars);

// Returns the root of the tree built using algorithm 431
// of the book. Remember to NOT include characters that
// have frequency of zero.
Node *buildBinaryTree(const int *freq);

void getCodewords(Node *root, string codewords[]);

char getChar(Node *root, bit_buffer &buf);

// Count the frequencies of each character. So
// freq['a'] gives the number of occurrences of
// 'a' in the data string.
//
// To iterate over a string:
//    for (int i = 0; i < data.size(); ++i) {
//      cout << data[i];
//    }
void countFrequencies(const string &data, int *freq);

// This function is provided for you.
string getHeader(int *freq);

// To compress the given data you will need to do
// a number of things, including building the
// frequency table, building the binary tree,
// getting the codewords, writing a header (see
// below) and writing the data itself. You should
// write auxiliary functions and test them as you
// go.
//
// A getHeader() function is provided to you to
// get the header in proper format. It will look
// something like the following. The first number
// is the number of characters with non-zero
// frequency.
// 6
// a 45
// b 13
// c 12
// d 16
// e 9
// f 5
//
// After writing the header you will write the data
// itself in compressed format.
string compressData(const string &data);

// This function reads frequencies from the header,
// builds the binary tree and uses the tree itself
// (not the codewords) to uncompress the data.
string uncompressData(const string &data);

