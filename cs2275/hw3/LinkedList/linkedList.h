#pragma once

#include <iostream>
#include <utility>

template <typename T>
class LinkedList;

template <typename T>
std::ostream& operator<<(std::ostream&, const LinkedList<T>&);

template <typename T>
class Node
{
public:
	//Do not allow copying or moving a node:
	Node(const Node<T>& copy) = delete;
	Node(Node<T>&& copy) = delete;
	Node<T>& operator=(const Node<T>& rhs) = delete;
	Node<T>& operator=(Node<T>&& rhs) = delete;

	Node<T>* getNextNode() { return next_; }
	const Node<T>* getNextNode() const { return next_; }

	Node<T>* getPreviousNode() { return previous_; }
	const Node<T>* getPreviousNode() const { return previous_; }

	T& get() { return element_; }
	const T& get() const { return element_; }

	//Prevent allocating nodes on the stack.

	/**
	 * Creates a new node and returns a reference to it. Passes ownership.
	 */
	static Node<T>& createNode() { return *new Node<T>(); }

	/**
	 * Creates a new node and returns a reference to it. Passes ownership.
	 */
	static Node<T>& createNode(const T& content) { return *new Node<T>(content); }

	/**
	 * Creates a new node and returns a reference to it. Passes ownership.
	 */
	static Node<T>& createNode(T&& content) { return *new Node<T>(std::move(content)); }

private:
	T element_;
	Node<T>* next_;
	Node<T>* previous_;

	friend class LinkedList<T>;

	//Prevent allocating nodes on the stack.
	Node(): element_(), next_(nullptr), previous_(nullptr) { }
	explicit Node(const T& content): element_(content), next_(nullptr), previous_(nullptr) { }
	explicit Node(T&& content): element_(std::move(content)), next_(nullptr), previous_(nullptr) { }
	~Node() = default;
};

template <typename T>
class LinkedList
{
public:
	LinkedList(): first_(nullptr), last_(nullptr) { }

	//Rule of 5
	~LinkedList();
	LinkedList(const LinkedList<T>& other);
	LinkedList(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& other);
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;

	void swap(LinkedList<T>& other) noexcept;

	void insertBeginning(Node<T>& node);
	Node<T>& insertBeginning(const T& item);
	Node<T>& insertBeginning(T&& item);

	void insertEnd(Node<T>& node);
	Node<T>& insertEnd(const T& item);
	Node<T>& insertEnd(T&& item);

	void insertAfter(Node<T>& n, Node<T>& next);
	Node<T>& insertAfter(Node<T>& n, const T& item);
	Node<T>& insertAfter(Node<T>& n, T&& item);

	void insertBefore(Node<T>& n, Node<T>& before);
	Node<T>& insertBefore(Node<T>& n, const T& item);
	Node<T>& insertBefore(Node<T>& n, T&& item);

	void remove(Node<T>& n);
	void append(const LinkedList<T>& other);
	void append(LinkedList<T>&& other);

	void swap(Node<T>& left, Node<T>& right) noexcept;

	Node<T>& getNode(int index);
	const Node<T>& getNode(int index) const;

private:
	Node<T>* first_;
	Node<T>* last_;

	void insertBeginningUnchecked(Node<T>& node) noexcept;
	void insertEndingUnchecked(Node<T>& node) noexcept;
	void insertAfterUnchecked(Node<T>& node, Node<T>& after) noexcept;
	void insertBeforeUnchecked(Node<T>& node, Node<T>& before) noexcept;

	static void attemptVerifyUnused(Node<T>& node);
	void attemptVerifyPartOfThisList(Node<T>& node);

	friend std::ostream& operator<< <T>(std::ostream&, const LinkedList<T>&);
};

/**
 * Deletes this list.
 */
template <typename T>
LinkedList<T>::~LinkedList()
{
	Node<T>* chain = first_;

	//Delete every node in the chain.
	while (chain != nullptr)
	{
		Node<T>* next = chain->getNextNode();
		chain->next_ = chain->previous_ = nullptr;
		delete chain;

		chain = next;
	}

	//Set pointers to null
	first_ = nullptr;
	last_ = nullptr;
}

/**
 * Copies other into this list.
 */
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	//If the other is empty, initialize this emptily.
	if (other.first_ == nullptr)
	{
		first_ = nullptr;
		last_ = nullptr;
		return;
	}

	//Copy the first element of the chain.
	Node<T>* chain_to_copy = other.first_;
	first_ = new Node<T>(chain_to_copy->element_);
	last_ = first_;

	try
	{
		while ((chain_to_copy = chain_to_copy->next_) != nullptr)
		{
			last_->next_ = new Node<T>(chain_to_copy->element_);
			last_ = last_->next_;
		}
	}
	catch (...)
	{
		//Cleanup if there is an exception while copying
		//Since we are using new in a loop.
		this->~LinkedList();

		//Rethrow exception
		throw;
	}
}

/**
 * Copies the other linked list leaving the other list in
 * an unspecified valid state.
 */
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept : LinkedList()
{
	swap(other);
}

/**
 * Copies the contents of the other list into this list.
 */
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	//copy-swap idiom
	LinkedList<T> copy(other);
	swap(copy);
	return *this;
}

/**
 * Moves the content of the other list into this list.
 */
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept
{
	swap(other);
	return *this;
}

/**
 * Swaps the contents of this list with other.
 */
template <typename T>
void LinkedList<T>::swap(LinkedList<T>& other) noexcept
{
	using std::swap;
	swap(first_, other.first_);
	swap(last_, other.last_);
}

/**
 * Adds the node to the front of this list and assumes ownership of the node.
 * Undefined behavior will result if the node is already part of a list.
 * It is highly recommended that you do not use this function.
 */
template <typename T>
void LinkedList<T>::insertBeginning(Node<T>& node)
{
	attemptVerifyUnused(node);
	insertBeginningUnchecked(node);
}

/**
 * Inserts the item at the beginning of this list and
 * returns a reference to the node containing the item.
 */
template <typename T>
Node<T>& LinkedList<T>::insertBeginning(const T& item)
{
	Node<T>& n = *new Node<T>(item);
	insertBeginningUnchecked(n);
	return n;
}

/**
 * Inserts the item at the beginning of this list and returns
 * a reference to the node containing the item.
 */
template <typename T>
Node<T>& LinkedList<T>::insertBeginning(T&& item)
{
	Node<T>& n = *new Node<T>(std::move(item));
	insertBeginningUnchecked(n);
	return n;
}

/**
 * Inserts the node at the end of this list. The list then assumes ownership of the node.
 * Please note that inserting a node that's already been inserted into a list has
 * undefined behavior.
 * If the node is null, nothing happens.
 */
template <typename T>
void LinkedList<T>::insertEnd(Node<T>& node)
{
	attemptVerifyUnused(node);
	insertEndingUnchecked(node);
}

/**
 * Inserts the item at the end of this list and returns a pointer
 * to the last node.
 */
template <typename T>
Node<T>& LinkedList<T>::insertEnd(const T& item)
{
	Node<T>& n = *new Node<T>(item);
	insertEndingUnchecked(n);
	return n;
}

/**
 * Inserts the item at the end of this list and returns a pointer
 * to the last node.
 */
template <typename T>
Node<T>& LinkedList<T>::insertEnd(T&& item)
{
	Node<T>& n = *new Node<T>(std::move(item));
	insertEndingUnchecked(n);
	return n;
}

/**
 * Inserts next after n. If n is null, this will throw an exception.
 * If next is null, nothing will happen. This list will assume ownership of next.
 * Undefined behavior will happen if next has been inserted into another list.
 */
template <typename T>
void LinkedList<T>::insertAfter(Node<T>& n, Node<T>& next)
{
	attemptVerifyUnused(next);
	attemptVerifyPartOfThisList(n);
	insertAfterUnchecked(n, next);
}

/**
 * Adds the item to the end of this list and returns the node containing it.
 */
template <typename T>
Node<T>& LinkedList<T>::insertAfter(Node<T>& n, const T& item)
{
	attemptVerifyPartOfThisList(n);

	Node<T>& ret = *new Node<T>(item);
	insertAfterUnchecked(n, ret);
	return ret;
}

/**
 * Adds the item to the end of this list and returns the node containing it.
 */
template <typename T>
Node<T>& LinkedList<T>::insertAfter(Node<T>& n, T&& item)
{
	attemptVerifyPartOfThisList(n);

	Node<T>& ret = *new Node<T>(std::move(item));
	insertAfterUnchecked(n, ret);
	return ret;
}

/**
 * Inserts before before n. If n is null, this will throw an exception.
 * If before is null, nothing will happen. This list will assume ownership of before.
 * Undefined behavior will happen if before has been inserted into another list.
 */
template <typename T>
void LinkedList<T>::insertBefore(Node<T>& n, Node<T>& before)
{
	attemptVerifyUnused(before);
	attemptVerifyPartOfThisList(n);
	insertBeforeUnchecked(n, before);
}

/**
 * Adds the item before node and returns the node containing it.
 */
template <typename T>
Node<T>& LinkedList<T>::insertBefore(Node<T>& n, const T& item)
{
	attemptVerifyPartOfThisList(n);

	Node<T>& ret = *new Node<T>(item);
	insertBeforeUnchecked(n, ret);
	return ret;
}

/**
 * Adds the item before node and returns the node containing it.
 */
template <typename T>
Node<T>& LinkedList<T>::insertBefore(Node<T>& n, T&& item)
{
	attemptVerifyPartOfThisList(n);

	Node<T>& ret = *new Node<T>(std::move(item));
	insertBeforeUnchecked(n, ret);
	return ret;
}

/**
 * Removes and deletes the node from this list. All use of the node after
 * being removed is invalid.
 */
template <typename T>
void LinkedList<T>::remove(Node<T>& n)
{
	attemptVerifyPartOfThisList(n);

	if (n.next_ != nullptr)
	{
		n.next_->previous_ = n.previous_;
	}
	else
	{
		last_ = n.previous_;
	}

	if (n.previous_ != nullptr)
	{
		n.previous_->next_ = n.next_;
	}
	else
	{
		first_ = &n;
	}

	delete &n;
}

/**
 * Appends the contents of the other list to this one.
 */
template <typename T>
void LinkedList<T>::append(const LinkedList<T>& other)
{
	Node<T>* n = other.first_;

	while (n != nullptr)
	{
		insertEnd(n->element_);
		n = n->next_;
	}
}

/**
 * Moves the contents of the other list to the end of this one.
 */
template <typename T>
void LinkedList<T>::append(LinkedList<T>&& other)
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
 * Swaps the contents of the two nodes. The two nodes don't have to
 * be part of this list.
 */
template <typename T>
void LinkedList<T>::swap(Node<T>& left, Node<T>& right) noexcept
{
	using std::swap;
	swap(left->element_, right->element_);
}

/**
 * Retrieves the node at the specified index.
 * Will thrown an exception if the index is negative or past
 * the end of the list. 0-indexed.
 */
template <typename T>
Node<T>& LinkedList<T>::getNode(int index)
{
	//https://stackoverflow.com/a/123995/4230423
	return const_cast<Node<T>&>(
		static_cast<const LinkedList<T>&>(*this).getNode(index)
	);
}

/**
 * Retrieves the node at the specified index.
 * Will thrown an exception if the index is negative or past
 * the end of the list. 0-indexed.
 */
template <typename T>
const Node<T>& LinkedList<T>::getNode(int index) const
{
	if (index < 0) throw std::invalid_argument("Index cannot be negative.");

	Node<T>* n = first_;

	for (auto i = 0; i < index && n != nullptr; i++)
	{
		n = n->next_;
	}

	if (n == nullptr) throw std::invalid_argument("Index cannot be go past the end of this list.");

	return *n;
}

/**
 * Inserts the given node at the beginning of this list without
 * doing argument checking or throwing. Takes ownership of the node.
 */
template <typename T>
void LinkedList<T>::insertBeginningUnchecked(Node<T>& node) noexcept
{
	if (first_ == nullptr)
	{
		last_ = first_ = &node;
		node.next_ = node.previous_ = nullptr;
	}
	else
	{
		node.next_ = first_;
		node.previous_ = nullptr;
		first_->previous_ = &node;
		first_ = &node;
	}
}

/**
 * Inserts the given node at the ending of this list without
 * doing argument checking or throwing. Takes ownership of the node.
 */
template <typename T>
void LinkedList<T>::insertEndingUnchecked(Node<T>& node) noexcept
{
	if (last_ == nullptr)
	{
		first_ = last_ = &node;
		node.next_ = node.previous_ = nullptr;
	}
	else
	{
		node.previous_ = last_;
		node.next_ = nullptr;
		last_->next_ = &node;
		last_ = &node;
	}
}

/**
 * Inserts after after node without doing argument checking or throwing.
 * Takes ownership of after.
 */
template <typename T>
void LinkedList<T>::insertAfterUnchecked(Node<T>& node, Node<T>& after) noexcept
{
	if (node.next_ == nullptr)
	{
		after.previous_ = &node;
		after.next_ = nullptr;
		last_ = node.next_ = &after;
	}
	else
	{
		after.previous_ = &node;
		after.next_ = node.next_;
		node.next_->previous_ = &after;
		node.next_ = &after;
	}
}

/**
 * Inserts before before node without doing argument checking or throwing.
 * Takes ownership of before.
 */
template <typename T>
void LinkedList<T>::insertBeforeUnchecked(Node<T>& node, Node<T>& before) noexcept
{
	if (node.previous_ == nullptr)
	{
		before.next_ = &node;
		before.previous_ = nullptr;
		first_ = node.previous_ = &before;
	}
	else
	{
		before.next_ = &node;
		before.previous_ = node.previous_;
		node.previous_->next_ = &before;
		node.previous_ = &before;
	}
}

/**
 * Throws an exception if we can detect that the node has already been inserted into a list.
 * This detection fails if the node is the only node in a list.
 */
template <typename T>
void LinkedList<T>::attemptVerifyUnused(Node<T>& node)
{
	if (node.next_ != nullptr || node.previous_ != nullptr)
	{
		throw std::invalid_argument("Node is already part of a list and you are invoking undefined behavior.");
	}
}

/**
 * Throws an exception if the node is not in this list.
 * It can only detect this if the node is at the end or beginning of a list that
 * isn't this one or if this list is empty.
 */
template <typename T>
void LinkedList<T>::attemptVerifyPartOfThisList(Node<T>& node)
{
	if ((node.next_ == nullptr && &node != last_)
		|| (node.previous_ == nullptr && &node != first_)
		|| (first_ == nullptr))
	{
		throw std::invalid_argument(
			"You are attempting to add a node before or after a node that is not"
			"part of this list. Warning: you are invoking undefined behavior."
		);
	}
}

/**
 * Outputs the contents of this list to the given stream.
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& rhs)
{
	Node<T>* n = rhs.first_;

	out << '[';
	if (n != nullptr)
	{
		while (true)
		{
			out << n->get();
			n = n->getNextNode();

			//Outputs a comma between each element.
			if (n != nullptr)
			{
				out << ", ";
			}
			else
			{
				break;
			}
		}
	}
	out << ']';


	return out;
}
