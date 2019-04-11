//------------------------------------------------------------
//
// CS 3385
// Project p565
//
// In this project you will implement disjoint sets, also called
// union find sets. Your disjoint sets will be an implementation
// of the data structure shown in figure 21.2 of the textbook.
// Your union() function will use the weighted-union heuristic,
// which means that you will need to maintain the size of the
// set.
//
// After implementing your data structure you will apply it to
// a real-world application: finding connected components in
// images. This is often used in image segmentation.
//
// Files to submit:
//   * DisjointSet.h
//   * DisjointSet.cpp
// 
//------------------------------------------------------------

#include <fstream>
#include <iostream>

#include "./util.h"
#include "./DisjointSet.h"

using namespace std;

//------------------------------------------------------------
// Tests
//------------------------------------------------------------
int runTests()
{
    
    int numFails = 0;
    int testNum = 0;
    
    {
        // This test matches figure 21.2 in the book.
        Node *f = makeSet();
        Node *g = makeSet();
        Node *d = makeSet();
        Node *c = makeSet();
        Node *h = makeSet();
        Node *e = makeSet();
        Node *b = makeSet();
        TEST(find(f) == f);
        TEST(find(g) == g);
        TEST(find(f) != find(g));
        
        makeUnion(f, g);
        TEST(find(f) == f);
        TEST(find(g) == f);
        
        makeUnion(f, d);
        TEST(find(f) == f);
        TEST(find(g) == f);
        TEST(find(d) == f);
        
        // Heads up! g and d are in the same set!
        makeUnion(g, d);
        TEST(find(f) == f);
        TEST(find(g) == f);
        TEST(find(d) == f);
        
        makeUnion(c, h);
        makeUnion(e, b);
        makeUnion(h, b);
        TEST(find(c) == c);
        TEST(find(h) == c);
        TEST(find(e) == c);
        TEST(find(b) == c);
        
        // This is different from figure 21.2. The figure doesn't use a
        // weighted union heuristic, but we do, so we merge set S1
        // (using the names given in the book) into set S2.
        makeUnion(g, e);
        TEST(find(f) == c);
        TEST(find(g) == c);
        TEST(find(d) == c);
        TEST(find(c) == c);
        TEST(find(h) == c);
        TEST(find(e) == c);
        TEST(find(b) == c);
    }
    
    {
        // It's helpful to be able to store data as we'll see when
        // we find connected components in images. In this case,
        // just store an int for simplicity.
        Node *f = makeSet(3);
        Node *g = makeSet(8);
        Node *d = makeSet(12);
        TEST(find(f)->data() == 3);
        TEST(find(g)->data() == 8);
        TEST(find(d)->data() == 12);
        
        makeUnion(f, g);
        TEST(find(f)->data() == 3);
        TEST(find(g)->data() == 3);
        TEST(find(d)->data() == 12);
        
        makeUnion(f, d);
        TEST(find(f)->data() == 3);
        TEST(find(g)->data() == 3);
        TEST(find(d)->data() == 3);
    }
    
    {
        // This function will help you see how to access an image.
        // Your result should look like test4/5-quantized-target.bmp.
        // There is no unit test for this. Your result images will
        // be visually inspected.
        quantizeImage("test4.bmp", "test4-quantized.bmp", 10);
        quantizeImage("test5.bmp", "test5-quantized.bmp", 4);
    }
    
    {
        // Finds the connected components of an image and writes a new
        // image where each connected component has its own color.
        // For tests 1 and 2 there is a testx-cc-target.bmp file to
        // make sure yours is correct. The colors may be different
        // due to different random number generators on different
        // compilers.
        //
        // There is no unit test for this. Your result images will
        // be visually inspected.
        connectedComponents("test1.bmp", "test1-cc.bmp", 10);
        connectedComponents("test2.bmp", "test2-cc.bmp", 10);
        connectedComponents("test3.bmp", "test3-cc.bmp", 10);
        connectedComponents("test4.bmp", "test4-cc.bmp", 10);
        connectedComponents("test5.bmp", "test5-cc.bmp", 4);
    }
    
    const int numSuccesses = testNum - numFails;
    cout << numSuccesses << "/" << testNum << " tests succeeded" << endl;
    
    return numFails;
}

int main(int argc, char **argv)
{
    return runTests();
}

