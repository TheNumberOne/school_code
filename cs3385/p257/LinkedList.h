#pragma once

// Provides I/O
#include <iostream>
#include <sstream>
#include <string>
#include "HashTable.h"

//------------------------------------------------------------
// ListNode class
// ListNodes are singly-linked.
//------------------------------------------------------------
template<typename T>
class ListNode {
public:
    explicit ListNode(const T &data) : _data(data), _next(nullptr) {}

    const T &data() const { return _data; }

    const ListNode *next() const { return _next; }

    ListNode *next() { return _next; }

    void setNext(ListNode *next) { _next = next; }

private:
    T _data;
    ListNode *_next;
};

//------------------------------------------------------------
// LinkedList class
//------------------------------------------------------------
template<typename T>
class LinkedList {
public:
    LinkedList() {
        _head = nullptr;
    }

    // Prevent copying
    LinkedList(const LinkedList<T> &) = delete;

    LinkedList<T> &operator=(const LinkedList<T> &) = delete;

    ~LinkedList() {
        ListNode<T> *node = _head;
        while (node != nullptr) {
            ListNode<T> *next = node->next();
            delete node;
            node = next;
        }
    }

    /**
     * Inserts the specified node at the beginning of this list and takes ownership of it.
     */
    void insert(ListNode<T> *node) noexcept {
        node->setNext(_head);
        _head = node;
        _size++;
    }

    /**
     * Finds the node corresponding to the specified key.
     */
    const ListNode<T> *find(const T &key) const {
        for (ListNode<T> *n = _head; n != nullptr; n = n->next()) {
            if (n->data() == key) {
                return n;
            }
        }
        return nullptr;
    }

    /**
     * Removes the node corresponding to the key from this list.
     */
    void remove(const T &key) {
        ListNode<T> *prev = nullptr;
        ListNode<T> *n = _head;
        for (; n != nullptr; prev = n, n = n->next()) {
            if (n->data() == key) break;
        }

        // We didn't find it
        if (n == nullptr) return;

        if (prev != nullptr) {
            prev->setNext(n->next());
        } else {
            _head = n->next();
        }

        _size--;
        delete n;
    }

    friend std::ostream &operator<<(std::ostream &out, const LinkedList &list) {
        ListNode<T> *node = list._head;
        while (node != nullptr) {
            out << node->data();
            if (node->next() != nullptr) {
                out << " -> ";
            }
            node = node->next();
        }
        return out;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    size_t size() const { return _size; }

private:
    ListNode<T> *_head;
    size_t _size = 0;

    template<typename U, typename V>
    friend
    class HashTable;
};
