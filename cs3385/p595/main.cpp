//------------------------------------------------------------
//
// CS 3385
// Project p595
//
// In this project you will implement a graph using an adjacency
// list and implement breadth-first search.
//
// After implementing your data structure you will apply it to
// the Six Degrees of Kevin Bacon game. Two movie database files
// are included: movies1deg.txt and movies2deg45min.txt. The first
// file stores only the movies with Kevin Bacon in them, and thus
// only actors with a Bacon number of one, and will be used for
// developing and testing your code. The second file stores data
// out one more degree, but it takes longer to process, so we'll
// only work with it after the code is basically done.
//
// All descriptions in this project use the term "actor" to refer
// to both actors and actresses for simplicity.
//
// You can check your answers with oracleofbacon.org. While the
// number of degrees should match for each test (up to two degrees)
// the movies may not necessarily match since there are multiple
// paths back to Kevin Bacon for a given actor.
//
// Once you are passing all of the unit tests then implement
// the play() function in bacon.cpp. This allows a user to play
// the Six Degrees of Kevin Bacon at the command line. To test,
// run the program with arguments "-play movies1deg.txt". Here's
// some example output:
//
//     Please enter an actor's name (press Enter to quit): Moore, Demi
//     Moore, Demi has a Bacon number of 1
//     Moore, Demi was in A Few Good Men (1992) with Bacon, Kevin (I)
//     
//     Please enter an actor's name (press Enter to quit): Hanks, Tom
//     Hanks, Tom has a Bacon number of 1
//     Hanks, Tom was in Apollo 13 (1995/I) with Bacon, Kevin (I)
//     
//     Please enter an actor's name (press Enter to quit): McAvoy, James
//     McAvoy, James has a Bacon number of 1
//     McAvoy, James was in X: First Class (2011) with Bacon, Kevin (I)
//     
//     Please enter an actor's name (press Enter to quit): 
//     
// Once you have it working, then try with "-play movies2deg45min.txt" and
// you can get actors with a bacon number of 2:
//     
//     Please enter an actor's name (press Enter to quit): Weller, Peter (I)
//     Weller, Peter (I) has a Bacon number of 2
//     Weller, Peter (I) was in RoboCop (1987) with Wise, Ray (I)
//     Wise, Ray (I) was in X: First Class (2011) with Bacon, Kevin (I)
//     
//     Please enter an actor's name (press Enter to quit): Olivier, Laurence
//     Olivier, Laurence has a Bacon number of 2
//     Olivier, Laurence was in Carrie (1952) with Albert, Eddie (I)
//     Albert, Eddie (I) was in The Big Picture (1989) with Bacon, Kevin (I)
//     
//     Please enter an actor's name (press Enter to quit): Fisher, Carrie (I)
//     Fisher, Carrie (I) has a Bacon number of 2
//     Fisher, Carrie (I) was in Scream 3 (2000) with Campbell, Neve
//     Campbell, Neve was in Wild Things (1998) with Bacon, Kevin (I)
//     
//     Please enter an actor's name (press Enter to quit): 
//
// Keep in mind that obscure actors may not be in the dataset since we're
// filtering out any actor that has not been in at least 45 movies. You'll
// be surprised, however, at just how many actors are in there!
//
// Implementing the Six Degrees game will be worth 20% of the grade.
//
// Files to submit:
//   * Graph.h
//   * bacon.h
//   * bacon.cpp
// 
//------------------------------------------------------------

#include <iostream>
#include <functional>

#include "./util.h"
#include "./Graph.h"
#include "./bacon.h"

using namespace std;

//------------------------------------------------------------
// Tests
//------------------------------------------------------------
int runTests()
{
    
    int numFails = 0;
    int testNum = 0;
    
    {
        // Create a Graph class. It should have a vector of Vertex
        // pointers. Implement the Graph class in Graph.h.
        Graph G;
        // Add a function to add vertices.
        Vertex *A = G.addVertex("A");
        Vertex *B = G.addVertex("B");
        TEST_EQUAL(G.numVertices(), 2);
        TEST_EQUAL(A->data(), "A");
        TEST_EQUAL(B->data(), "B");
        // The best way to implement getVertex is for your Graph
        // class to have a hashtable mapping vertex names to the
        // vertices themselves. You can do this as follows:
        //     std::unordered_map<std::string, Vertex*> _key2vertex;
        // Then, to check if it exists,
        //     bool exists = (_key2vertex.find(name) != _key2vertex.end());
        // Finally, to add and retrieve a vertex,
        //     _key2vertex[name] = v; // add
        //     Vertex* v = _key2vertex[name]; // retrieve
        TEST_EQUAL(G.getVertex("A"), A);
        
        // ensureVertex should check if a vertex with the given
        // name already exists and return the existing vertex if
        // it does. Add a new vertex otherwise.
        Vertex *AA = G.ensureVertex("A");
        TEST_EQUAL(A, AA);
        TEST_EQUAL(G.numVertices(), 2);
        
        Vertex *BB = G.ensureVertex("B");
        TEST_EQUAL(G.numVertices(), 2);
        TEST_EQUAL(B, BB);
        
        Vertex *C = G.ensureVertex("C");
        TEST_EQUAL(G.numVertices(), 3);
        
        // Implement the data structure in figure 22.1(b) of the book.
        // Each node in a linked list should store a pointer to the
        // neighbor's Vertex object (the book stores the name of the
        // vertex but you should store a pointer for efficiency) and
        // should also store a name for the edge.
        G.addEdge(A, B, "A-B");
        TEST(G.hasEdge(A, B));
        TEST(G.hasEdge(B, A));
        TEST(!G.hasEdge(A, A));
        TEST_EQUAL(G.getEdgeData(A, B), "A-B");
        TEST_EQUAL(G.getEdgeData(B, A), "A-B");
        
        Vertex *D = G.addVertex("D");
        Vertex *E = G.ensureVertex("E");
        G.addEdge(A, C, "Hello world");
        G.addEdge(D, C, "");
        G.addEdge(E, C, "");
        G.addEdge(E, D, "");
        TEST(G.hasEdge(A, B));
        TEST(G.hasEdge(E, C));
        TEST(G.hasEdge(E, D));
        TEST(G.hasEdge(D, E));
        TEST(!G.hasEdge(A, D));
        TEST(!G.hasEdge(A, A));
        TEST_EQUAL(G.getEdgeData(C, A), "Hello world");
        
        // The bread-first search should set values in the Vertex
        // objects, such as d, pi and color (white, gray and black).
        // You may want to use std::queue<Vertex*> for the queue.
        G.bfs(A);
        TEST_EQUAL(B->pi(), A);
        TEST_EQUAL(C->pi(), A);
        TEST_EQUAL(D->pi(), C);
        TEST_EQUAL(E->pi(), C);
        TEST_EQUAL(A->d(), 0);
        TEST_EQUAL(B->d(), 1);
        TEST_EQUAL(C->d(), 1);
        TEST_EQUAL(D->d(), 2);
        TEST_EQUAL(E->d(), 2);
        
        // // You are encouraged but not required to implement a
        // // toDot() function for debugging purposes. The following
        // // call to toDot() results in the following:
        // //    graph G {
        // //    A[label="A\nd = 0"]
        // //    B[label="B\nd = 1"]
        // //    C[label="C\nd = 1"]
        // //    D[label="D\nd = 2"]
        // //    E[label="E\nd = 2"]
        // //      A -- C
        // //      A -- B
        // //      C -- D
        // //      C -- E
        // //      D -- E
        // //    }
        // cout << G.toDot() << endl;
    }
    
    {
        // This function is declared but commented out in bacon.h.
        // Implement it in bacon.cpp. See the comments in the
        // skeleton function.
        Graph G = buildBaconGraph("movies1deg.txt");
        
        Vertex *kb = G.getVertex("Bacon, Kevin (I)");
        Vertex *dm = G.getVertex("Moore, Demi");
        Vertex *eh = G.getVertex("Hirsch, Emile");
        Vertex *pw = G.getVertex("Weller, Peter (I)");
        Vertex *vj = G.getVertex("Johnson, Van (I)");
        Vertex *cc = G.getVertex("Charisse, Cyd");
        G.bfs(kb);
        // We only test the distance since the actual movies
        // and actors can vary based on ordering of the bfs search.
        TEST_EQUAL(dm->d(), 1);
        // A possible edge, dm->edgeData(dm->pi()), might be
        // A Few Good Men (1992).
        TEST_EQUAL(eh->d(), 1);
        // A possible edge, eh->edgeData(dm->pi()), might be
        // The Air I Breathe (2007).
        
        // The following actors have a bacon number of 2, so they won't
        // be present in this dataset.
        TEST_EQUAL(pw, NULL);
        TEST_EQUAL(vj, NULL);
        TEST_EQUAL(cc, NULL);
    }
    
    {
        // This test will take longer than the others. Uncomment
        // it once everything else is working.
        Graph G = buildBaconGraph("movies2deg45min.txt");
        
        Vertex *kb = G.getVertex("Bacon, Kevin (I)");
        Vertex *dm = G.getVertex("Moore, Demi");
        Vertex *eh = G.getVertex("Hirsch, Emile");
        Vertex *pw = G.getVertex("Weller, Peter (I)");
        Vertex *vj = G.getVertex("Johnson, Van (I)");
        Vertex *cc = G.getVertex("Charisse, Cyd");
        G.bfs(kb);
        
        TEST_EQUAL(dm->d(), 1);
        TEST_EQUAL(eh->d(), 1);
        TEST_EQUAL(pw->d(), 2);
        TEST_EQUAL(vj->d(), 2);
        TEST_EQUAL(cc->d(), 2);
    }
    
    const int numSuccesses = testNum - numFails;
    cout << numSuccesses << "/" << testNum << " tests succeeded" << endl;
    
    return numFails;
}

int main(int argc, char **argv)
{
    if (argc > 1 && string(argv[1]) == "-play") {
        play(argv[2]);
        return 0;
    }
    return runTests();
}

