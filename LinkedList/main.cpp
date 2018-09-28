// LinkedList.cpp : Defines the entry point for the application.
//

#include "linkedList.h"
#include <string>
#include <memory>

using namespace std;

/**
 * Custom exception that won't be able to be caught without a catch all clause
 */
class MyException{};

/**
 * This class fails sometimes when it is copied.
 */
class FailingCopy
{
public:
	FailingCopy()
	{
		static auto i = 0;
		index_ = i++;
	}

	FailingCopy(const FailingCopy& other): copied_(true), index_(other.index_)
	{
		static auto i = 0;

		//Creates 5 and then fails.
		if (i++ >= 5) throw MyException();

		cout << "Copied object " << index_ << endl;
	}

	FailingCopy(FailingCopy&& other) = default;

	~FailingCopy()
	{
		if (copied_)
		{
			cout << "Deleted copied object " << index_ << "." << endl;
		}
	}

	FailingCopy& operator=(const FailingCopy&) = default;
	FailingCopy& operator=(FailingCopy&&) = default;
private:
	bool copied_ = false;
	int index_ = 0;
};

int main()
{
	cout << "Creating a list full of 100 dummy objects." << endl;
	LinkedList<FailingCopy> list;

	for (auto i = 0; i < 100; ++i)
	{
		list.insertBeginning(FailingCopy());
	}

	//Test memory leak in copy constructor.
	//Run with something like valgrind to make sure this works.
	try
	{
		cout << "Testing memory leak in copy constructor. Attempting to copy the list of objects" << endl;
		LinkedList<FailingCopy> copiedList(list);
	}
	catch (MyException&)
	{
		cout << "Caught my exception. 5 copied items should be deleted." << endl;	
	}

	cout << "Creating empty list" << endl;
	LinkedList<std::string> strings; //[]
	cout << "List: " << strings << endl;

	cout << "Inserting 'Hello' at beginning of list" << endl;
	Node<std::string>& helloNode = strings.insertBeginning("Hello"); // [Hello]
	cout << "List: " << strings << endl;

	cout << "Inserting 'World' after 'Hello'" << endl;
	strings.insertAfter(helloNode, "World"); //[Hello, World]
	cout << "List: " << strings << endl;

	cout << "Copying the list" << endl;
	LinkedList<std::string> stringsCopy = strings;
	cout << "Copy: " << stringsCopy << endl; //[Hello, World]
	cout << "List: " << strings << endl;//[Hello, World]

	cout << "Inserting 'Sunny' after 'Hello' in copy" << endl;
	Node<std::string>& helloNodeCopy = stringsCopy.getNode(0);
	stringsCopy.insertAfter(helloNodeCopy, "Sunny");//[Hello, Sunny, World]
	cout << "Copy: " << stringsCopy << endl;

	cout << "Appending original list to the copy" << endl;
	stringsCopy.append(strings);//[Hello, Sunny, World, Hello, World]
	cout << "Copy: " << stringsCopy << endl;

	cout << "Inserting 'Ending' at the end of the copy" << endl;
	stringsCopy.insertEnd("Ending"); //[Hello, Sunny, World, Hello, World, Ending]
	cout << "Copy: " << stringsCopy << endl;

	cout << "Removing the node at index 3 in the copy" << endl;
	stringsCopy.remove(stringsCopy.getNode(3)); //[Hello, Sunny, World, World, Ending]
	cout << "Copy: " << stringsCopy << endl;

	cout << "Inserting 'Beginning' before the first 'Hello' in this list" << endl;
	stringsCopy.insertBefore(helloNodeCopy, "Beginning"); //[Beginning, Hello, Sunny, World, World, Ending]
	cout << "Copy: " << stringsCopy << endl;

	cout << "Original list: " << strings << endl; //[Hello, World]


	//Test moving logic works
	cout << "Creating only movable unique pointers to 5 and 10." << endl;
	auto five = make_unique<int>(5);
	auto ten = make_unique<int>(10);

	cout << "Five address: " << five.get() << endl;
	cout << "Ten address: " << ten.get() << endl;

	cout << "Creating a list to hold them" << endl;
	LinkedList<unique_ptr<int>> notCopyable;

	cout << "Moving pointer to 5 to beginning of list" << endl;
	notCopyable.insertBeginning(std::move(five));

	cout << "Moving the list to another location via move constructor" << endl;
	auto moved = std::move(notCopyable);

	cout << "Moving the list to another location via move assignment operator" << endl;
	LinkedList<unique_ptr<int>> moveAssigned;
	moveAssigned = std::move(moved);

	cout << "Moving 10 to the end of the list" << endl;
	moveAssigned.insertEnd(std::move(ten));

	cout << "Address of first element: " << moveAssigned.getNode(0).get().get() << endl; //pointer to five
	cout << "Address of next element: " << moveAssigned.getNode(1).get().get() << endl; //pointer to ten
	cout << "Value of first element: " << *moveAssigned.getNode(0).get() << endl; //5
	cout << "Value of next element: " << *moveAssigned.getNode(1).get() << endl; //10

	return 0;
}
