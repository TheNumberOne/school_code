//------------------------------------------------------------
//
// CS 3385
// Project p157
//
// Very rarely do modern heaps store integers as elements. In
// this project you will be modifying your heap to store
// Patient objects (like Patients in a hospital) instead of
// integers. You'll then be adding necessary functionality
// so you can use the heap as a priority queue. This would
// be important in an emergency room situation. A person
// with a serious injury would be higher priority than
// a person with a head cold.
//
// One more general comment about this project. So far, we've
// pretty much been coding algorithms from the book verbatim.
// In this project we'll depart from that. The book's
// algorithms assume that the array stores integer "keys"
// and that the objects are stored elsewhere. Modern programming
// languages like C++, C# and Java have features that make
// it convenient and efficient to store the objects right
// in the array. So while the algorithms in the book might
// give you some direction, you'll mostly just be figuring
// this out on your own.
//
// Start by copying your Heap.h and Heap.cpp to this directory.
// Then add the following to the end of the include list in
// Heap.h:
//
//    #include "Patient.h"
//
// Then make the necessary changes in Heap.h and Heap.cpp to
// store Patient objects. There are two approaches to doing
// this: 1) change the type of the array A in Heap.h to
// Patient*. Then compile and fix all the compile errors. This
// approach may not be very pleasant. 2) Comment-out all
// functions in the Heap class, change the type of array A,
// then slowly add functions back in, testing all the way.
// The unit tests are designed to help with this approach.
//
// Note that toDot() will continue to work fine after you've
// converted to using Patient objects instead of integers.
//
// For the arrayEquals() function (included in this file)
// to work properly, you will need to change your at()
// function as follows:
//
//    Patient at(int i) const;
//
// You will need to add the const keyword both in the .h and
// the .cpp files. You should do this for parent(), left() and
// right() also.
//
// Files to submit:
//   * Heap.h
//   * Heap.cpp
// 
//------------------------------------------------------------

#include <iostream>

#include "./Heap.h"

using namespace std;

#define TEST(test) { \
  testNum++; \
  if (!(test)) { \
    cerr << "Test " << testNum << " failed" << endl; \
    numFails++; \
  } \
}

bool arrayEquals(const Heap &h, const Patient *A, int n);

int runTests() {
    int numFails = 0;
    int testNum = 0;

    {
        Patient A[] = {
                Patient("George McClellan", 1),
                Patient("George Mead", 2),
                Patient("Robert E. Lee", 3),
        };
        Heap h(A, 3, 3);
        TEST(h == A);
        TEST(h.at(0).name() == "George McClellan");
        TEST(h.at(2).name() == "Robert E. Lee");
        TEST(h.left(0) == 1);
        TEST(h.parent(1) == 0);
    }

    {
        Patient A[] = {
                Patient("George McClellan", 1),
                Patient("George Mead", 2),
                Patient("Robert E. Lee", 3),
        };
        Heap h(A, 3, 3);
        h.maxHeapify(0);
        Patient target[] = {
                Patient("Robert E. Lee", 3),
                Patient("George Mead", 2),
                Patient("George McClellan", 1),
        };
        TEST(arrayEquals(h, target, 3));
        h.maxHeapify(0);
        TEST(arrayEquals(h, target, 3));
        h.maxHeapify(1);
        TEST(arrayEquals(h, target, 3));
        h.maxHeapify(2);
        TEST(arrayEquals(h, target, 3));
    }

    {
        Patient A[] = {
                Patient("George McClellan", 4),
                Patient("George Mead", 1),
                Patient("Robert E. Lee", 3),
                Patient("John Pope", 2),
                Patient("Stonewall Jackson", 16),
                Patient("J.E.B. Stuart", 9),
                Patient("James Longstreet", 10),
                Patient("Ulysses S. Grant", 14),
                Patient("Robert Anderson", 8),
                Patient("George Custer", 7),
        };
        Heap h(A, 10, 10);
        h.buildMaxHeap();
        Patient target[] = {
                Patient("Stonewall Jackson", 16),
                Patient("Ulysses S. Grant", 14),
                Patient("James Longstreet", 10),
                Patient("Robert Anderson", 8),
                Patient("George Custer", 7),
                Patient("J.E.B. Stuart", 9),
                Patient("Robert E. Lee", 3),
                Patient("John Pope", 2),
                Patient("George McClellan", 4),
                Patient("George Mead", 1),
        };
        TEST(arrayEquals(h, target, 10));
    }

    {
        Patient A[] = {
                Patient("George McClellan", 4),
                Patient("George Mead", 1),
                Patient("Robert E. Lee", 3),
                Patient("John Pope", 2),
                Patient("Stonewall Jackson", 16),
                Patient("J.E.B. Stuart", 9),
                Patient("James Longstreet", 10),
                Patient("Ulysses S. Grant", 14),
                Patient("Robert Anderson", 8),
                Patient("George Custer", 7),
        };
        Heap h(A, 10, 10);
        h.heapsort();
        Patient target[] = {
                Patient("George Mead", 1),
                Patient("John Pope", 2),
                Patient("Robert E. Lee", 3),
                Patient("George McClellan", 4),
                Patient("George Custer", 7),
                Patient("Robert Anderson", 8),
                Patient("J.E.B. Stuart", 9),
                Patient("James Longstreet", 10),
                Patient("Ulysses S. Grant", 14),
                Patient("Stonewall Jackson", 16),
        };
        std::cout << h << std::endl;
        TEST(arrayEquals(h, target, 10));
    }

    {
        Patient A[] = {
                Patient("George Mead", 1),
                Patient("George McClellan", 4),
                Patient(),
                Patient(),
                Patient(),
                Patient(),
                Patient(),
        };
        Heap h(A, 7, 2);
        h.buildMaxHeap();
        Patient next = h.extractMax();
        TEST(next.name() == "George McClellan");
        TEST(h.max().name() == "George Mead");

        h.insert(Patient("Robert E. Lee", 3));
        TEST(h.max().name() == "Robert E. Lee");

        h.insert(Patient("John Pope", 2));
        TEST(h.max().name() == "Robert E. Lee");

        h.insert(Patient("Stonewall Jackson", 16));
        TEST(h.max().name() == "Stonewall Jackson");

        next = h.extractMax();
        TEST(next.name() == "Stonewall Jackson");

        next = h.extractMax();
        TEST(next.name() == "Robert E. Lee");

        next = h.extractMax();
        TEST(next.name() == "John Pope");
    }

    const int numSuccesses = testNum - numFails;
    cout << numSuccesses << "/" << testNum << " tests succeeded" << endl;

    return numFails;
}

int main() {
    return runTests();
}

bool arrayEquals(const Heap &h, const Patient *A, int n) {
    for (int i = 0; i < n; ++i) {
        if (h.at(i) != A[i]) return false;
    }
    return true;
}

