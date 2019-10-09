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
template<typename T, typename Hash>
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
        KeyValue(const int key, const T &value) {
            _key = key;
            _value = value;
        }

        int key() const { return _key; }

        const T &value() const { return _value; }

        bool operator==(const KeyValue &rhs) const {
            return _key == rhs._key;
        }

    private:
        int _key;
        T _value;
    };

    //--------------------------------------------------
    // Remaining implementation of the HashTable.
    //--------------------------------------------------
public:
    explicit HashTable(size_t capacity) : _bins(capacity), _a(new LinkedList<KeyValue>[capacity]) {}

    HashTable(const HashTable<T, Hash> &) = delete;

    HashTable<T, Hash> &operator=(const HashTable<T, Hash> &) = delete;

    ~HashTable() { delete[] _a; }

    /**
     * Returns the total number of items in this hashtable.
     */
    size_t size() const { return _size; }

    /**
     * Returns the total number of items in the bucket with the specified index
     */
    size_t size(size_t i) const {
        return _a[i].size();
    }

    /**
     * Puts the key value pair into this dictionary.
     */
    void put(int key, T value) {
        KeyValue toInsert{key, value};
        auto &b = bin(key);
        if (!b.find(toInsert)) {
            b.insert(new ListNode<KeyValue>(toInsert));
            _size++;
        }
    }

    /**
     * Returns if this contains the specified key
     */
    bool contains(int key) const {
        return bin(key).find({key, {}}) != nullptr;
    }

    /**
     * Returns the specified value at the specified index.
     */
    const T &get(int key) const {
        auto node = bin(key).find({key, {}});
        if (node == nullptr) throw std::runtime_error("No value for key");
        return node->data().value();
    }

    /**
     * Copies the keys into the passed array.
     */
    void getKeys(int out[]) {
        size_t j = 0;
        for (size_t i = 0; i < _bins; i++) {
            auto h = _a[i]._head;
            while (h != nullptr) {
                out[j++] = h->data().key();
                h = h->next();
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &out, HashTable &t) {
        size_t n = t.size();
        auto keys = new int[n];
        t.getKeys(keys);
        for (int i = 0; i < n; ++i) {
            const int key = keys[i];
            out << t.get(key) << "; ";
        }
        delete[] keys;
        return out;
    }

private:
    Hash _h;
    size_t _size = 0;
    size_t _bins;
    LinkedList<KeyValue> *_a;

    LinkedList<KeyValue> &bin(int key) {
        return _a[_h(key, (int) _bins)];
    }

    const LinkedList<KeyValue> &bin(int key) const {
        return _a[_h(key, (int) _bins)];
    }
};
