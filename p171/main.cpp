//------------------------------------------------------------
//
// CS 3385
// Project p171
//
// The first thing you'll do in this project is to copy and
// modify slightly bubblesort to get you used to working with
// templates. You'll then copy and templatize your implementation
// of insertion sort from project p18 (place your code in
// insertion.h) to further understand templates. You'll then
// be ready to implement a templatized version of quicksort.
//
// Both bubble sorts go in bubble.h, insertion sort goes in
// insertion.h and quicksort functions go in quicksort.h.
//
// Files to submit:
//   * bubble.h
//   * insertion.h
//   * quicksort.h
// 
//------------------------------------------------------------

#include <iostream>

#include "./util.h"
#include "./bubble.h"
#include "insertion.h"
#include "quicksort.h"

using namespace std;

//------------------------------------------------------------
// Tests
//------------------------------------------------------------
int runTests() {

    int numFails = 0;
    int testNum = 0;

    {
        int A[] = {1, 4, 2, 3};
        bubblesort(A, 4);
        int target[] = {1, 2, 3, 4};
        TEST(arrayEquals(A, target, 4));
    }

    {
        Song A[] = {
                Song("Superstition", "Stevie Wonder"),
                Song("Hello Again", "The Cars"),
                Song("Yellow Submarine", "The Beatles"),
                Song("Big Country", "Bela Fleck"),
                Song("Major Tom", "Peter Schilling"),
        };
        printArray(A, 5);
        bubblesort(A, 5);
        printArray(A, 5);

        Song target[] = {
                Song("Big Country", "Bela Fleck"),
                Song("Hello Again", "The Cars"),
                Song("Major Tom", "Peter Schilling"),
                Song("Superstition", "Stevie Wonder"),
                Song("Yellow Submarine", "The Beatles"),
        };
        TEST(arrayEquals(A, target, 5));
    }

    {
        Person A[] = {
                Person("Sergei Rachmaninoff", 37),
                Person("Igor Stravinsky", 17),
                Person("Alexander Borodin", 23),
                Person("Modest Mussorgsky", 24),
                Person("Nikolai Rimsky-Korsakov", 52),
                Person("Pyotr Ilyich Tchaikovsky", 70),
                Person("Dmitri Shostakovich", 30),
                Person("Alexander Scriabin", 39),
                Person("Anton Rubinstein", 44),
                Person("Sergei Prokofiev", 23),
                Person("Aram Khachaturian", 56)
        };
        printArray(A, 11);
        bubblesort(A, 11);
        printArray(A, 11);

        Person target[] = {
                Person("Alexander Borodin", 23),
                Person("Alexander Scriabin", 39),
                Person("Anton Rubinstein", 44),
                Person("Aram Khachaturian", 56),
                Person("Dmitri Shostakovich", 30),
                Person("Igor Stravinsky", 17),
                Person("Modest Mussorgsky", 24),
                Person("Nikolai Rimsky-Korsakov", 52),
                Person("Pyotr Ilyich Tchaikovsky", 70),
                Person("Sergei Prokofiev", 23),
                Person("Sergei Rachmaninoff", 37),
        };
        TEST(arrayEquals(A, target, 11));
    }

    {
        int A[] = {1, 4, 2, 3};
        reverseBubblesort(A, 4);
        int target[] = {4, 3, 2, 1};
        TEST(arrayEquals(A, target, 4));
    }

    {
        Song A[] = {
                Song("Superstition", "Stevie Wonder"),
                Song("Hello Again", "The Cars"),
                Song("Yellow Submarine", "The Beatles"),
                Song("Big Country", "Bela Fleck"),
                Song("Major Tom", "Peter Schilling"),
        };
        reverseBubblesort(A, 5);
        printArray(A, 5);

        Song target[] = {
                Song("Yellow Submarine", "The Beatles"),
                Song("Superstition", "Stevie Wonder"),
                Song("Major Tom", "Peter Schilling"),
                Song("Hello Again", "The Cars"),
                Song("Big Country", "Bela Fleck"),
        };
        TEST(arrayEquals(A, target, 5));
    }

    {
        Person A[] = {
                Person("Sergei Rachmaninoff", 37),
                Person("Igor Stravinsky", 17),
                Person("Alexander Borodin", 23),
                Person("Modest Mussorgsky", 24),
                Person("Nikolai Rimsky-Korsakov", 52),
                Person("Pyotr Ilyich Tchaikovsky", 70),
                Person("Dmitri Shostakovich", 30),
                Person("Alexander Scriabin", 39),
                Person("Anton Rubinstein", 44),
                Person("Sergei Prokofiev", 23),
                Person("Aram Khachaturian", 56)
        };
        reverseBubblesort(A, 11);
        printArray(A, 11);

        Person target[] = {
                Person("Sergei Rachmaninoff", 37),
                Person("Sergei Prokofiev", 23),
                Person("Pyotr Ilyich Tchaikovsky", 70),
                Person("Nikolai Rimsky-Korsakov", 52),
                Person("Modest Mussorgsky", 24),
                Person("Igor Stravinsky", 17),
                Person("Dmitri Shostakovich", 30),
                Person("Aram Khachaturian", 56),
                Person("Anton Rubinstein", 44),
                Person("Alexander Scriabin", 39),
                Person("Alexander Borodin", 23),
        };
        TEST(arrayEquals(A, target, 11));
    }

    {
        int A[] = {1, 4, 2, 3};
        insertionSort(A, 4);
        int target[] = {1, 2, 3, 4};
        TEST(arrayEquals(A, target, 4));
    }

    {
        Song A[] = {
                Song("Superstition", "Stevie Wonder"),
                Song("Hello Again", "The Cars"),
                Song("Yellow Submarine", "The Beatles"),
                Song("Big Country", "Bela Fleck"),
                Song("Major Tom", "Peter Schilling"),
        };
        insertionSort(A, 5);

        Song target[] = {
                Song("Big Country", "Bela Fleck"),
                Song("Hello Again", "The Cars"),
                Song("Major Tom", "Peter Schilling"),
                Song("Superstition", "Stevie Wonder"),
                Song("Yellow Submarine", "The Beatles"),
        };
        TEST(arrayEquals(A, target, 5));
    }

    {
        Person A[] = {
                Person("Sergei Rachmaninoff", 37),
                Person("Igor Stravinsky", 17),
                Person("Alexander Borodin", 23),
                Person("Modest Mussorgsky", 24),
                Person("Nikolai Rimsky-Korsakov", 52),
                Person("Pyotr Ilyich Tchaikovsky", 70),
                Person("Dmitri Shostakovich", 30),
                Person("Alexander Scriabin", 39),
                Person("Anton Rubinstein", 44),
                Person("Sergei Prokofiev", 23),
                Person("Aram Khachaturian", 56)
        };
        insertionSort(A, 11);

        Person target[] = {
                Person("Alexander Borodin", 23),
                Person("Alexander Scriabin", 39),
                Person("Anton Rubinstein", 44),
                Person("Aram Khachaturian", 56),
                Person("Dmitri Shostakovich", 30),
                Person("Igor Stravinsky", 17),
                Person("Modest Mussorgsky", 24),
                Person("Nikolai Rimsky-Korsakov", 52),
                Person("Pyotr Ilyich Tchaikovsky", 70),
                Person("Sergei Prokofiev", 23),
                Person("Sergei Rachmaninoff", 37),
        };
        TEST(arrayEquals(A, target, 11));
    }

    {
        int A[] = {2, 8, 7, 1, 3, 5, 6, 4};
        partition(A, 0, 7);
        int target[] = {2, 1, 3, 4, 7, 5, 6, 8};
        TEST(arrayEquals(A, target, 8));
    }

    {
        Song A[] = {
                Song("Superstition", "Stevie Wonder"),
                Song("Hello Again", "The Cars"),
                Song("Yellow Submarine", "The Beatles"),
                Song("Big Country", "Bela Fleck"),
                Song("Major Tom", "Peter Schilling"),
        };
        partition(A, 0, 4);
        Song target[] = {
                Song("Hello Again", "The Cars"),
                Song("Big Country", "Bela Fleck"),
                Song("Major Tom", "Peter Schilling"),
                Song("Superstition", "Stevie Wonder"),
                Song("Yellow Submarine", "The Beatles"),
        };
        TEST(arrayEquals(A, target, 5));
    }

    {
        int A[] = {1, 4, 2, 3};
        quicksort(A, 4);
        int target[] = {1, 2, 3, 4};
        TEST(arrayEquals(A, target, 4));
    }

    {
        Song A[] = {
                Song("Superstition", "Stevie Wonder"),
                Song("Hello Again", "The Cars"),
                Song("Yellow Submarine", "The Beatles"),
                Song("Big Country", "Bela Fleck"),
                Song("Major Tom", "Peter Schilling"),
        };
        quicksort(A, 5);
        Song target[] = {
                Song("Big Country", "Bela Fleck"),
                Song("Hello Again", "The Cars"),
                Song("Major Tom", "Peter Schilling"),
                Song("Superstition", "Stevie Wonder"),
                Song("Yellow Submarine", "The Beatles"),
        };
        TEST(arrayEquals(A, target, 5));
    }

    {
        Person A[] = {
                Person("Sergei Rachmaninoff", 37),
                Person("Igor Stravinsky", 17),
                Person("Alexander Borodin", 23),
                Person("Modest Mussorgsky", 24),
                Person("Nikolai Rimsky-Korsakov", 52),
                Person("Pyotr Ilyich Tchaikovsky", 70),
                Person("Dmitri Shostakovich", 30),
                Person("Alexander Scriabin", 39),
                Person("Anton Rubinstein", 44),
                Person("Sergei Prokofiev", 23),
                Person("Aram Khachaturian", 56)
        };
        quicksort(A, 11);
        Person target[] = {
                Person("Alexander Borodin", 23),
                Person("Alexander Scriabin", 39),
                Person("Anton Rubinstein", 44),
                Person("Aram Khachaturian", 56),
                Person("Dmitri Shostakovich", 30),
                Person("Igor Stravinsky", 17),
                Person("Modest Mussorgsky", 24),
                Person("Nikolai Rimsky-Korsakov", 52),
                Person("Pyotr Ilyich Tchaikovsky", 70),
                Person("Sergei Prokofiev", 23),
                Person("Sergei Rachmaninoff", 37),
        };
        TEST(arrayEquals(A, target, 11));
    }

    const int numSuccesses = testNum - numFails;
    cout << numSuccesses << "/" << testNum << " tests succeeded" << endl;

    return numFails;
}

int main() {
    return runTests();
}

