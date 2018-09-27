#pragma once

#include <iostream>

template<typename T>
class node
{
	T element_;
	node<T>* next_;
	node<T>* previous_;

public:
	node(): element_(), next_(nullptr), previous_(nullptr) { }
	explicit node(T content): element_(content), next_(nullptr), previous_(nullptr) { }

	node<T>* get_next_node() { return next_; }
	const node<T>* get_next_node() const { return next_; }

	node<T>* get_previous_node() { return previous_; }
	const node<T>* get_previous_node() const { return previous_; }
};

template<typename T>
class linked_list
{
	node<T>* first_;
	node<T>* last_;

public:
	linked_list(): first_(nullptr), last_(nullptr) {}
	~linked_list();
	linked_list(const linked_list<T> &other);
	linked_list(linked_list<T> &&other);
	linked_list<T>& operator=(const linked_list<T> &other);
	linked_list<T>& operator=(linked_list<T> &&other);
	void swap(linked_list<T> &other);

	void insert_beginning(node<T>* node);
	node<T>* insert_beginning(const T &item);
	node<T>* insert_beginning(T &&item);

	void insert_end(node<T>* node);
	node<T>* insert_end(const T &item);
	node<T>* insert_end(T &&item);

	void insert_after(node<T>* node, node<T>* next);
	node<T>* insert_after(node<T>* node, const T &item);
	node<T>* insert_after(node<T>* node, T &&item);

	void insert_before(node<T>* node, node<T>* before);
	node<T>* insert_before(node<T>* node, const T &item);
	node<T>* insert_before(node<T>* node, T &&item);

	void remove(node<T>* node);
	void append(const linked_list<T> &other);

	void swap(node<T>* left, node<T>* right);

	node<T>* get_node(int index);
	const node<T>* get_node(int index) const;

};
