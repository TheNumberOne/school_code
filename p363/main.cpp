//------------------------------------------------------------
//
// CS 3385
// Project p363
//
// In this project you will implement dynamic programming
// solutions to the cut rod and fibonacci problems using
// memoization.
//
// We won't call a memoized function with anything greater
// than n=100.
//
// File to submit:
//   * dynamic.h
// 
//------------------------------------------------------------

#include <iostream>

#include "./util.h"
#include "./dynamic.h"

using namespace std;

//------------------------------------------------------------
// Tests
//------------------------------------------------------------
int runTests() {

    int numFails = 0;
    int testNum = 0;

    {
        int callcount = 0;
        int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
        TEST(cutRodNaive(p, 1, callcount) == 1);
        TEST(cutRodNaive(p, 2, callcount) == 5);
        TEST(cutRodNaive(p, 3, callcount) == 8);
        TEST(cutRodNaive(p, 4, callcount) == 10);
        TEST(cutRodNaive(p, 5, callcount) == 13);
        TEST(cutRodNaive(p, 6, callcount) == 17);
        TEST(cutRodNaive(p, 7, callcount) == 18);
        TEST(cutRodNaive(p, 8, callcount) == 22);
        TEST(cutRodNaive(p, 9, callcount) == 25);
        TEST(cutRodNaive(p, 10, callcount) == 30);

        callcount = 0;
        cutRodNaive(p, 1, callcount);
        TEST(callcount == 2);

        callcount = 0;
        cutRodNaive(p, 4, callcount);
        TEST(callcount == 16);

        callcount = 0;
        cutRodNaive(p, 24, callcount);
        TEST(callcount == 16777216);
    }

    {
        int callcount = 0;
        int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
        TEST(cutRodMemo(p, 1, callcount) == 1);
        TEST(cutRodMemo(p, 5, callcount) == 13);
        TEST(cutRodMemo(p, 10, callcount) == 30);

        callcount = 0;
        cutRodMemo(p, 1, callcount);
        TEST(callcount == 2);

        callcount = 0;
        cutRodMemo(p, 4, callcount);
        TEST(callcount == 11);

        callcount = 0;
        cutRodMemo(p, 24, callcount);
        TEST(callcount == 301);
    }

    {
        // The fibonacci sequence is
        //  index: 0  1  2  3  4  5  6  7
        //  value: 1  1  2  3  5  8 13 21
        int callcount = 0;
        TEST(fibNaive(0, callcount) == 1);
        TEST(fibNaive(1, callcount) == 1);
        TEST(fibNaive(2, callcount) == 2);
        TEST(fibNaive(3, callcount) == 3);
        TEST(fibNaive(4, callcount) == 5);
        TEST(fibNaive(5, callcount) == 8);

        callcount = 0;
        fibNaive(0, callcount);
        TEST(callcount == 1);

        callcount = 0;
        fibNaive(4, callcount);
        TEST(callcount == 9);

        callcount = 0;
        fibNaive(34, callcount);
        TEST(callcount == 18454929);
    }

    {
        // The fibonacci sequence is
        //  index: 0  1  2  3  4  5  6  7
        //  value: 1  1  2  3  5  8 13 21
        int callcount = 0;
        TEST(fibMemo(0, callcount) == 1);
        TEST(fibMemo(1, callcount) == 1);
        TEST(fibMemo(2, callcount) == 2);
        TEST(fibMemo(3, callcount) == 3);
        TEST(fibMemo(4, callcount) == 5);
        TEST(fibMemo(5, callcount) == 8);

        callcount = 0;
        fibMemo(0, callcount);
        TEST(callcount == 1);

        callcount = 0;
        fibMemo(4, callcount);
        TEST(callcount == 7);

        callcount = 0;
        fibMemo(34, callcount);
        TEST(callcount == 67);
    }

    const int numSuccesses = testNum - numFails;
    cout << numSuccesses << "/" << testNum << " tests succeeded" << endl;

    return numFails;
}

int main() {
    return runTests();
}

