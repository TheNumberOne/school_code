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
	explicit node(const T &content): element_(content), next_(nullptr), previous_(nullptr) { }
	explicit node(T &&content): element_(content), next_(nullptr), previous_(nullptr) { }

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
	linked_list(linked_list<T> &&other) noexcept;
	linked_list<T>& operator=(const linked_list<T> &other);
	linked_list<T>& operator=(linked_list<T> &&other) noexcept;
	void swap(linked_list<T> &other) noexcept;

	void insert_beginning(node<T>* node);
	node<T>* insert_beginning(const T &item);
	node<T>* insert_beginning(T &&item);

	void insert_end(node<T>* node);
	node<T>* insert_end(const T &item);
	node<T>* insert_end(T &&item);

	void insert_after(node<T>* n, node<T>* next);
	node<T>* insert_after(node<T>* n, const T &item);
	node<T>* insert_after(node<T>* n, T &&item);

	void insert_before(node<T>* n, node<T>* before);
	node<T>* insert_before(node<T>* n, const T &item);
	node<T>* insert_before(node<T>* n, T &&item);

	void remove(node<T>* n);
	void append(const linked_list<T> &other);
	void append(linked_list<T> &&other);

	void swap(node<T>* left, node<T>* right);

	node<T>* get_node(int index);
	const node<T>* get_node(int index) const;
};

/**
 * Deletes this list.
 */
template <typename T>
linked_list<T>::~linked_list()
{
	auto node = first_;

	while (node != nullptr)
	{
		auto next = node->get_next_node();
		delete node;

		node = next;
	}

	first_ = nullptr;
	last_ = nullptr;
}

/**
 * Copies other into this list.
 */
template <typename T>
linked_list<T>::linked_list(const linked_list<T>& other)
{
	if (other.first_ != nullptr)
	{
		node<T>* chain_to_copy = other.first_;
		first_ = new node<T>(chain_to_copy->element_);
		last_ = first_;

		while ((chain_to_copy = chain_to_copy->next_) != nullptr)
		{
			last_->next_ = new node<T>(chain_to_copy->element_);
			last_ = last_->next_;
		}
	}
	else
	{
		first_ = nullptr;
		last_ = nullptr;
	}
}

/**
 * Copies the other linked list leaving the other list in
 * an unspecified valid state.
 */
template <typename T>
linked_list<T>::linked_list(linked_list<T>&& other) noexcept : linked_list() 
{
	swap(other);
}

/**
 * Copies the contents of the other list into this list.
 */
template <typename T>
linked_list<T>& linked_list<T>::operator=(const linked_list<T>& other)
{
	//copy-swap idiom
	linked_list<T> copy = other;
	swap(copy);
	return *this;
}

/**
 * Moves the content of the other list into this list.
 */
template <typename T>
linked_list<T>& linked_list<T>::operator=(linked_list<T>&& other) noexcept
{
	swap(other);
	return *this;
}

/**
 * Swaps the contents of this list with other.
 */
template <typename T>
void linked_list<T>::swap(linked_list<T>& other) noexcept
{
	using std::swap;
	swap(first_, other.first_);
	swap(last_, other.last_);
}

/**
 * Adds the node to the front of this list and assumes ownership of the node.
 * Undefined behavior will result if the node is already part of a list.
 * It is highly recommended that you do not use this function.
 * If the node is null, nothing happens.
 */
template <typename T>
void linked_list<T>::insert_beginning(node<T>* node)
{
	if (node == nullptr) return;

	if (first_ == nullptr)
	{
		last_ = first_ = node;
		node->next_ = node->previous_ = nullptr;
	}
	else
	{
		node->next_ = first_;
		node->previous_ = nullptr;
		first_->previous_ = node;
		first_ = node;
	}
}

/**
 * Inserts the item at the beginning of this list and
 * returns a pointer to the node containing the item.
 */
template <typename T>
node<T>* linked_list<T>::insert_beginning(const T& item)
{
	node<T>* n = new node<T>(item);
	insert_beginning(n);
	return n;
}

/**
 * Inserts the item at the beginning of this list and returns
 * a pointer to the node containing the item.
 */
template <typename T>
node<T>* linked_list<T>::insert_beginning(T&& item)
{
	node<T>* n = new node<T>(item);
	insert_beginning(n);
	return n;
}

/**
 * Inserts the node at the end of this list. The list then assumes ownership of the node.
 * Please note that inserting a node that's already been inserted into a list has
 * undefined behavior.
 * If the node is null, nothing happens.
 */
template <typename T>
void linked_list<T>::insert_end(node<T>* node)
{
	if (node == nullptr) return;

	if (last_ == nullptr)
	{
		first_ = last_ = node;
		node->next_ = node->previous_ = nullptr;
	}
	else
	{
		node->previous_ = last_;
		node->next_ = nullptr;
		last_->next_ = node;
		last_ = node;
	}
}

/**
 * Inserts the item at the end of this list and returns a pointer
 * to the last node.
 */
template <typename T>
node<T>* linked_list<T>::insert_end(const T& item)
{
	node<T>* n = new node<T>(item);
	insert_end(n);
	return n;
}

/**
 * Inserts the item at the end of this list and returns a pointer
 * to the last node.
 */
template <typename T>
node<T>* linked_list<T>::insert_end(T&& item)
{
	node<T>* n = new node<T>(item);
	insert_end(n);
	return n;
}

/**
 * Inserts next after n. If n is null, this will throw an exception.
 * If next is null, nothing will happen. This list will assume ownership of next.
 * Undefined behavior will happen if next has been inserted into another list.
 */
template <typename T>
void linked_list<T>::insert_after(node<T>* n, node<T>* next)
{
	if (n == nullptr) throw std::invalid_argument("Can't insert a node after a null node.");
	if (next == nullptr) return;
	
	if (n->next_ == nullptr)
	{
		next->previous_ = n;
		next->next_ = nullptr;
		last_ = n->next_ = next;
	}
	else
	{
		next->previous_ = n;
		next->next_ = n->next_;
		n->next_->previous_ = next;
		n->next_ = next;
	}
}

/**
 * Adds the item to the end of this list and returns the node containing it.
 */
template <typename T>
node<T>* linked_list<T>::insert_after(node<T>* n, const T& item)
{
	node<T>* ret = new node<T>(item);
	insert_after(n, ret);
	return ret;
}

/**
 * Adds the item to the end of this list and returns the node containing it.
 */
template <typename T>
node<T>* linked_list<T>::insert_after(node<T>* n, T&& item)
{	
	node<T>* ret = new node<T>(item);
	insert_after(n, ret);
	return ret;
}

/**
 * Inserts before before n. If n is null, this will throw an exception.
 * If before is null, nothing will happen. This list will assume ownership of before.
 * Undefined behavior will happen if before has been inserted into another list.
 */
template <typename T>
void linked_list<T>::insert_before(node<T>* n, node<T>* before)
{
	if (n == nullptr) throw std::invalid_argument("Can't insert a node after a null node.");
	if (before == nullptr) return;
	
	if (n->previous_ == nullptr)
	{
		before->next_ = n;
		before->previous_ = nullptr;
		first_ = n->previous_ = before;
	}
	else
	{
		before->next_ = n;
		before->previous_ = n->previous_;
		n->previous_->next_ = before;
		n->previous_ = before;
	}
}

/**
 * Adds the item before node and returns the node containing it.
 */
template <typename T>
node<T>* linked_list<T>::insert_before(node<T>* n, const T& item)
{
	node<T>* ret = new node<T>(item);
	insert_before(n, ret);
	return ret;
}
/**
 * Adds the item before node and returns the node containing it.
 */
template <typename T>
node<T>* linked_list<T>::insert_before(node<T>* n, T&& item)
{
	node<T>* ret = new node<T>(item);
	insert_before(n, ret);
	return ret;
}

/**
 * Removes and deletes the node from this list. All use of the node after
 * being removed is invalid.
 */
template <typename T>
void linked_list<T>::remove(node<T>* n)
{
	if (n->next_ != nullptr)
	{
		n->next_->previous_ = n->previous_;
	}
	else
	{
		last_ = n->previous_;
	}

	if (n->previous_ != nullptr)
	{
		n->previous_->next_ = n->next_;
	}
	else
	{
		first_ = n;
	}

	delete n;
}

/**
 * Appends the contents of the other list to this one.
 */
template <typename T>
void linked_list<T>::append(const linked_list<T>& other)
{
	auto n = other.first_;
	
	while (n != nullptr)
	{
		insert_end(n->element_);
		n = n->next_;
	}
}

/**
 * Moves the contents of the other list to the end of this one.
 */
template <typename T>
void linked_list<T>::append(linked_list<T>&& other)
{
	if (other.first_ != nullptr)
	{
		last_->next_ = other.first_;
		last_->next_->previous_ = last_;
		last_ = other.last_;
		other.last_ = other.first_ = nullptr;
	}
}

/**
 * Swaps the contents of the two nodes.
 */
template <typename T>
void linked_list<T>::swap(node<T>* left, node<T>* right)
{
	using std::swap;
	swap(left->element_, right->element_);
}

/**
 * Retrieves the node at the specified index.
 * Behavior is unspecified if the index is negative or past
 * the end of the list. 0-indexed.
 */
template <typename T>
node<T>* linked_list<T>::get_node(int index)
{
	auto n = first_;

	while (index --> 0) n = first_->next_;

	return n;
}

/**
 * Retrieves the node at the specified index.
 * Behavior is unspecified if the index is negative or past
 * the end of the list. 0-indexed.
 */
template <typename T>
const node<T>* linked_list<T>::get_node(int index) const
{
	auto n = first_;

	while (index --> 0) n = first_->next_;

	return n;
}
