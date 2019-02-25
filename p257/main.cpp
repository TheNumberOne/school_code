//------------------------------------------------------------
//
// CS 3385
// Project p257
//
// In this project you will be implementing a chained hash table.
//
// You will be using the templated LinkedList you made in the
// binary tree project. If it isn't working then it is the
// first thing you will want to work on. Make sure it passes
// all tests in project p246 before bringing it into this
// project. You may in the course of this project find that you
// need to add some (minimal) additional functionality to your
// LinkedList.
//
// To start, you will implement the DivHash class in hash.h. You
// will then create the MultHash function in hash.h (see 
// instructions in hash.h)
//
// Once you have your hash functions implemented, you will
// implement HashTable in HashTable.h. Instructions below
// will guide you through this process.
//
// Be sure to use the code checker (linked to from the syllabus
// web page) to make sure your code will work when graded!
//
// Files to submit:
//   * LinkedList.h
//   * hash.h
//   * HashTable.h
// 
//------------------------------------------------------------

#include <iostream>
#include <sstream>

#include "./util.h"
#include "./hash.h"
#include "./HashTable.h"
#include "./Student.h"

using namespace std;

//------------------------------------------------------------
// Tests
//------------------------------------------------------------
int runTests() {

  int numFails = 0;
  int testNum = 0;

 //  {
 //    DivHash divHash;
 //    // DivHash is to be implemented in hash.h
 //    TEST(divHash(0, 3) == 0);
 //    TEST(divHash(1, 3) == 1);
 //    TEST(divHash(3, 3) == 0);
 //    TEST(divHash(5, 3) == 2);

 //    TEST(divHash(0, 31) == 0);
 //    TEST(divHash(18, 31) == 18);
 //    TEST(divHash(1003, 31) == 11);
 //    TEST(divHash(59372592, 31) == 28);

 //    MultHash multHash;
 //    // MultHash is to be implemented in hash.h
 //    TEST(multHash(0, 31) == 0);
 //    TEST(multHash(18, 31) == 3);
 //    TEST(multHash(1003, 31) == 27);
 //    TEST(multHash(59372592, 31) == 26);
 //  }

 //  {
 //    HashTable<string, DivHash> hashTable(10);
 //    // Returns the number of elements in the linked list at index 0 of hashTable's array of linked lists
 //    TEST(hashTable.size(0) == 0);
 //    // Returns the number of elements in the linked list at index 1 of hashTable's array of linked lists
 //    TEST(hashTable.size(1) == 0);
 //    // Returns the total number of elements in the hash table (across all of hashTable's array of linked lists)
 //    TEST(hashTable.size() == 0);

 //    hashTable.put(0, "A");
 //    // Puts the value "A" in the HashTable with the key 0 (note key does not necessarily equal index)
 //    // It may help to reference the previous project to see how to insert elements into a LinkedList
 //    TEST(hashTable.size(0) == 1);
 //    TEST(hashTable.size(1) == 0);
 //    TEST(hashTable.size() == 1);

 //    hashTable.put(10, "B");
 //    TEST(hashTable.size(0) == 2);
 //    TEST(hashTable.size(1) == 0);
 //    TEST(hashTable.size() == 2);

 //    hashTable.put(5, "C");
 //    hashTable.put(15, "D");
 //    hashTable.put(25, "E");
 //    TEST(hashTable.size(0) == 2);
 //    TEST(hashTable.size(1) == 0);
 //    TEST(hashTable.size(5) == 3);
 //    TEST(hashTable.size() == 5);

 //    // For the contains() and get() functions, you will not be able to use
 //    // LinkedList's find() function (you might consider why this is true.)
 //    // Instead, add a getHead() function to LinkedList and
 //    // then you can iterate through the list comparing the
 //    // key of the KeyValue pairs to get the correct KeyValue.
 //    TEST(hashTable.contains(0));
 //    TEST(hashTable.contains(10));
 //    TEST(hashTable.contains(15));
 //    TEST(!hashTable.contains(12));

 //    // the get() function should return the value of the KeyValue pair
 //    // and should throw an error if the key is not found
 //    string s = hashTable.get(0);
 //    TEST(s == "A");
 //    TEST(hashTable.get(10) == "B");
 //    TEST(hashTable.get(5) == "C");
 //    TEST(hashTable.get(15) == "D");
 //    TEST(hashTable.get(25) == "E");

 //    const int n = hashTable.size();
 //    int* keys = new int[n];
 //    // the getKeys() function should populate the array passed as a parameter
 //    // will the keys for each of the KeyValue elements in hashTable
 //    hashTable.getKeys(keys);
 //    for (int i = 0; i < n; ++i) {
 //      const int key = keys[i];
 //      TEST(hashTable.contains(key));
 //    }
 //    delete [] keys;

 //    // TODO: uncomment the output operator overload function in HashTable.
 //    cout << hashTable << endl;
 //    stringstream ss;
 //    ss << hashTable;
 //    string str = ss.str();
 //    TEST(str.find("A") != string::npos);
 //    TEST(str.find("B") != string::npos);
 //    TEST(str.find("C") != string::npos);
 //    TEST(str.find("D") != string::npos);
 //    TEST(str.find("E") != string::npos);
 //    TEST(str.find("F") == string::npos);
 //  }

 //  {
 //    HashTable<string, MultHash> hashTable(10);
 //    // Returns the number of elements in the linked list at index 0
 //    TEST(hashTable.size(0) == 0);
 //    // Returns the number of elements in the linked list at index 1
 //    TEST(hashTable.size(1) == 0);
 //    // Returns the total number of elements in the hash table
 //    TEST(hashTable.size() == 0);

 //    hashTable.put(0, "A");
 //    hashTable.put(12, "B");
 //    hashTable.put(23, "C");
 //    TEST(hashTable.size(0) == 1);
 //    TEST(hashTable.size(1) == 0);
 //    TEST(hashTable.size(2) == 1);
 //    TEST(hashTable.size(4) == 1);
 //    TEST(hashTable.size() == 3);
 //  }

 //  {
 //    HashTable<Student, DivHash> hashTable(10);
 //    Student students[] = {
 //      Student("Joe", 331829),
 //      Student("Sally", 46841),
 //      Student("Jill", 357911),
 //      Student("Zeke", 8784642),
 //    };
 //    for (int i = 0; i < 4; ++i) {
 //      hashTable.put(students[i].id(), students[i]);
 //    }
 //    TEST(hashTable.size(1) == 2);
 //    TEST(hashTable.size(9) == 1);
 //    TEST(hashTable.size() == 4);

 //    TEST(hashTable.contains(331829));
 //    TEST(!hashTable.contains(9));

 //    Student s = hashTable.get(331829);
 //    TEST(s.name() == "Joe");
 
 //    cout << hashTable << endl;
 //    stringstream ss;
 //    ss << hashTable;
 //    string str = ss.str();
 //    TEST(str.find("Joe") != string::npos);
 //    TEST(str.find("Sally") != string::npos);
 //    TEST(str.find("Jill") != string::npos);
 //    TEST(str.find("Zeke") != string::npos);
 //    TEST(str.find("Frank") == string::npos);
 //    TEST(str.find("George") == string::npos);
 //    TEST(str.find("Harry") == string::npos);
 //    TEST(str.find("Kristina") == string::npos);
 //    TEST(str.find("Angela") == string::npos);
 //    TEST(str.find("Laura") == string::npos);
 // }

  const int numSuccesses = testNum - numFails;
  cout << numSuccesses << "/" << testNum << " tests succeeded" << endl;

  return numFails;
}

int main() {
  return runTests();
}

