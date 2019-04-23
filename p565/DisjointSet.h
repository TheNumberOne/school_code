#pragma once

#include <cstddef>
#include <string>

// Your Node and DisjointSet classes will have references to each other.
// Circular references are handled by
//   1) making sure each least one of the references is a pointer.
//   2) declaring one of the classes before it is defined.
// For example,
//
//   // declaration of DisjointSet
//   class DisjointSet;
//
//   class Node {
//     // reference to DisjointSet
//   };
//
//   // definition of DisjointSet
//   class DisjointSet {
//   };

// TODO: place Node and DisjointSet classes here

class DisjointSet;

class Node
{
public:
    Node() = default;
    explicit Node(int data): _data(data) {}
    
    int data() const;
    void data(int data);

private:
    int _data = 0;
    Node *_next = nullptr;
    DisjointSet *_owner = nullptr;
    friend DisjointSet;
    friend Node *find(Node *x);
    friend void makeUnion(Node* x, Node* y);
};

Node *makeSet();

// // A node can hold data.
 Node* makeSet(int data);

Node *find(Node *x);

// // If x is greater than or equal to y, then merge y into x.
// // Otherwise, merge x into y. After merging, be sure to delete
// // one of the disjoint sets or you will have memory leaks.
// // For example, if merging y into x, then after merging
// // you would do something like
// //     delete y->set();
// // You do not need to delete any nodes, since they are
// // simply transferred from one set to another.
// //
// // This function is called makeUnion() rather than just
// // union() because union is a reserved word in C++.
 void makeUnion(Node* x, Node* y);

// // This function converts the input image to grayscale and quantizes the
// // intensities into numBins unique intensities. In effect, it reduces
// // the number of colors in the image. This function is a warm-up
// // to learn the Bitmap interface so you can use it for finding
// // connected components in the connectedComponents() function.
 void quantizeImage(
    const std::string &infile, const std::string &outfile, int numBins
);

// // This function finds all connected components in the quantized input
// // image and writes a new image with each connected component having
// // its own color.
 void connectedComponents(
     const std::string& infile, const std::string& outfile, int numBins);
