#pragma once

// Provides I/O
#include <iostream>
#include <sstream>
#include <string>

#include "./LinkedList.h"

//------------------------------------------------------------
// Instructions: your chained hash table will contain an array
// of linked lists (you're welcome to copy your templated
// LinkedList class from the binary tree project). Your
// array will be declared as
//    LinkedList<KeyValue>* A;
// In your constructor it will be allocated as
//    A = new LinkedList<KeyValue>[m];
//------------------------------------------------------------


// This class takes two template parameters: T is the type of value
// stored in the hash table. The second is the type of hash
// function to use. In member functions of HashTable,
// you can hash a key as follows:
//    int key = ...
//    Hash h;
//    int hash = h(key);
template <typename T, typename Hash>
class HashTable {
 private:
  //--------------------------------------------------
  // Utility class. The chains will hold instances of
  // KeyValue. The KeyValue stores both the key and
  // the value. This class is an inner class of
  // HashTable.
  //--------------------------------------------------
  class KeyValue {
   public:
    KeyValue() {}
    KeyValue(const int key, const T& value) {
      _key = key;
      _value = value;
    }
    int key() const { return _key; }
    const T& value() const { return _value; }
    bool operator==(const KeyValue& rhs) {
      return _key == rhs._key;
    }
   private:
    int _key;
    T _value;
  };

  //--------------------------------------------------
  // Remaining implementation of the HashTable.
  //--------------------------------------------------


  // TODO: uncomment this function after implementing getKeys().
  // friend std::ostream& operator<<(std::ostream& out, HashTable& t) {
  //   const int n = t.size();
  //   int* keys = new int[n];
  //   t.getKeys(keys);
  //   for (int i = 0; i < n; ++i) {
  //     const int key = keys[i];
  //     out << t.get(key) << "; ";
  //   }
  //   delete [] keys;
  //   return out;
  // }

 private:
  Hash _h;
};
