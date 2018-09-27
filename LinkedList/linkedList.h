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
	linked_list(const linked_list<T> &other);
};
