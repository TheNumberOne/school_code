#pragma once

// Provides I/O
#include <iostream>
#include <sstream>
#include <string>

//------------------------------------------------------------
// ListNode class
// ListNodes are singly-linked.
//------------------------------------------------------------
template <typename T>
class ListNode {
 public:
  ListNode(const T& data) {
    _data = data;
    _next = NULL;
  }

  ListNode(const T& data, ListNode* next) {
    _data = data;
    _next = next;
  }

  const T& data() const { return _data; }
  const ListNode* next() const { return _next; }
  ListNode* next() { return _next; }
  void setNext(ListNode* next) { _next = next; }

 private:
  T _data;
  ListNode* _next;
};

//------------------------------------------------------------
// LinkedList class
//------------------------------------------------------------
template <typename T>
class LinkedList {
 public:
  LinkedList() {
    _head = NULL;
  }

  // TODO: implement - set node to _head. If _head is non-null
  // then update next pointers so that node->next() points to
  // _head.
  void insert(ListNode<T>* node) {
  }

  // TODO: implement
  ListNode<T>* find(const T& key) {
    return NULL;
  }

  // Removes and deletes the first node in the linked list that has
  // data equal to key. To delete a node:
  //
  //   ListNode<T>* node = ...
  //   delete node;
  void remove(const T& key) {
  }

  friend std::ostream& operator<<(std::ostream& out, const LinkedList& list) {
    ListNode<T>* node = list._head;
    while (node != NULL) {
      out << node->data();
      if (node->next() != NULL) {
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

 private:
  ListNode<T>* _head;
};
