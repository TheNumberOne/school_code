// LinkedList.cpp : Defines the entry point for the application.
//

#include "LinkedList.h"
#include <string>
#include <memory>

using namespace std;

class my_exception{};

/**
 * This class fails sometimes when it is copied.
 */
class failing_copy
{
private:
	bool copied_ = false;
	int index_ = 0;
public:
	failing_copy()
	{
		static auto i = 0;
		index_ = i++;
	}

	failing_copy(const failing_copy& other): copied_(true), index_(other.index_)
	{
		static auto i = 0;

		//Creates 5 and then fails.
		if (i++ >= 5) throw my_exception();

		cout << "Copied " << index_ << endl;
	}

	failing_copy(failing_copy&& other) = default;

	~failing_copy()
	{
		if (copied_)
		{
			cout << "Deleted copied object " << index_ << "." << endl;
		}
	}

	failing_copy& operator=(const failing_copy&) = default;
	failing_copy& operator=(failing_copy&&) = default;
};


int main()
{
	linked_list<failing_copy> list;

	for (auto i = 0; i < 100; ++i)
	{
		list.insert_beginning(failing_copy());
	}

	//Test memory leak in copy constructor.
	//Run with something like valgrind to make sure this works.
	try
	{
		auto copied_list(list);
	}
	catch (my_exception&)
	{
		cout << "Caught my exception. 5 copied items should be deleted." << endl;	
	}

	linked_list<std::string> strings; //[]
	cout << strings << endl;

	auto* n = strings.insert_beginning("Hello"); // [Hello]
	cout << strings << endl;
	
	strings.insert_after(n, "World"); //[Hello, World]
	cout << strings << endl;

	auto strings_copy = strings;
	cout << strings_copy << endl; //[Hello, World]
	cout << strings << endl;//[Hello, World]

	n = strings_copy.get_node(0);
	strings_copy.insert_after(n, "Sunny");//[Hello, Sunny, World]
	cout << strings_copy << endl;

	strings_copy.append(strings);//[Hello, Sunny, World, Hello, World]
	cout << strings_copy << endl;

	strings_copy.insert_end("Ending"); //[Hello, Sunny, World, Hello, World, Ending]
	cout << strings_copy << endl;

	n = strings_copy.get_node(3); //Second Hello
	strings_copy.remove(n); //[Hello, Sunny, World, World, Ending]
	cout << strings_copy << endl;

	n = strings_copy.get_node(0); //Hello
	strings_copy.insert_before(n, "Beginning"); //[Beginning, Hello, Sunny, World, World, Ending]
	cout << strings_copy << endl;

	cout << strings << endl; //[Hello, World]


	//Test moving logic works
	auto five = make_unique<int>(5);
	auto ten = make_unique<int>(10);

	cout << "Five address: " << five.get() << endl;
	cout << "Ten address: " << ten.get() << endl;

	linked_list<unique_ptr<int>> not_copyable;
	not_copyable.insert_beginning(std::move(five));
	auto moved = std::move(not_copyable);

	linked_list<unique_ptr<int>> not_copyable2;
	not_copyable2 = std::move(moved);

	not_copyable2.insert_end(std::move(ten));

	cout << not_copyable2.get_node(0)->get().get() << endl; //pointer to five
	cout << not_copyable2.get_node(1)->get().get() << endl; //pointer to ten
	cout << *not_copyable2.get_node(0)->get() << endl; //5
	cout << *not_copyable2.get_node(1)->get() << endl; //10

	return 0;
}
