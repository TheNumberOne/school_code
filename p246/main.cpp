//------------------------------------------------------------
//
// CS 3385
// Project p246
//
// In this project you will be making additions to a linked
// list class and then creating a binary tree class from
// scratch.
//
// You can visualize your tree by calling toDot() and then
// plugging the result in to www.webgraphviz.com.
//
// Be sure to use the code checker (linked to from the syllabus
// web page) to make sure your code will work when graded.
//
// Files to submit:
//   * LinkedList.h
//   * BinaryTree.h
// 
//------------------------------------------------------------

#include <iostream>
#include <sstream>

#include "./util.h"
#include "./Person.h"
#include "./LinkedList.h"
#include "./BinaryTree.h"

using namespace std;

//------------------------------------------------------------
// Tests
//------------------------------------------------------------
int runTests() {

  int numFails = 0;
  int testNum = 0;

//   {
//     LinkedList<int> list;
//     list.insert(new ListNode<int>(3));
//     TEST(list.toString() == "3");

//     list.insert(new ListNode<int>(8));
//     cout << list << endl;
//     TEST(list.toString() == "8 -> 3");

//     list.insert(new ListNode<int>(5));
//     TEST(list.toString() == "5 -> 8 -> 3");

//     // find() needs to be implemented.
//     ListNode<int>* node;
//     node = list.find(8);
//     TEST(node->data() == 8);

//     node = list.find(7);
//     TEST(node == NULL);

//     // remove() needs to be implemented. It will use the
//     // find() function.
//     list.remove(8);
//     TEST(list.toString() == "5 -> 3");

//     list.insert(new ListNode<int>(2));
//     list.insert(new ListNode<int>(11));
//     list.insert(new ListNode<int>(7));
//     TEST(list.toString() == "7 -> 11 -> 2 -> 5 -> 3");

//     list.remove(7);
//     TEST(list.toString() == "11 -> 2 -> 5 -> 3");

//     list.remove(3);
//     TEST(list.toString() == "11 -> 2 -> 5");

//   }

//   {
//     LinkedList<string> list;
//     list.insert(new ListNode<string>("ABC"));
//     list.insert(new ListNode<string>("DEF"));
//     list.insert(new ListNode<string>("GHI"));
//     list.insert(new ListNode<string>("JKL"));
//     list.remove("GHI");
//     TEST(list.toString() == "JKL -> DEF -> ABC");
//   }

//   {
//     LinkedList<Person> list;
//     list.insert(new ListNode<Person>(Person("Theresa May", 55)));
//     list.insert(new ListNode<Person>(Person("Tony Blair", 70)));
//     list.insert(new ListNode<Person>(Person("Margaret Thatcher", 91)));
//     list.insert(new ListNode<Person>(Person("Winston Churchill", 88)));
//     cout << list.toString() << endl;
//     TEST(list.toString() == "Winston Churchill 88 -> Margaret Thatcher 91 -> Tony Blair 70 -> Theresa May 55");
//   }

//   {
//     // Implement BinaryTree in BinaryTree.h. Use the LinkedList class
//     // as a model.
//     BinaryTree<int> tree;
//     tree.setHead(new BNode<int>(3));
//     tree.head()->setLeft(new BNode<int>(8));
//     tree.head()->setRight(new BNode<int>(12));
//     TEST(tree.head()->data() == 3);
//     TEST(tree.head()->left()->data() == 8);
//     TEST(tree.head()->right()->data() == 12);
//     cout << tree.toDot() << endl;

//     // This syntax allows us to put a string literal in the code
//     // without escaping the double quotes. Please let Dr. Edwards
//     // know if it doesn't compile.
//     string target = R"str(
// digraph G {
// graph [ordering="out"]
// "3" -> "8"
// "3" -> "12"
// }
// )str";
//     // stringEquals tests strings and ignores whitespace.
//     TEST(stringEquals(tree.toDot(), target));

//     tree.head()->left()->setLeft(new BNode<int>(2));
//     tree.head()->left()->setRight(new BNode<int>(18));
//     tree.head()->right()->setLeft(new BNode<int>(5));
//     cout << tree.toDot() << endl;
//     target = R"str(
// digraph G {
// graph [ordering="out"]
// "3" -> "8"
// "3" -> "12"
// "8" -> "2"
// "8" -> "18"
// "12" -> "5"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));

//     // While the linked list find function is iterative, you
//     // will want to implement your tree algorithm recursively.
//     BNode<int>* n = tree.find(18, tree.head());
//     TEST(n->data() == 18);
//     n = tree.find(8, tree.head());
//     TEST(n->data() == 8);
//     n = tree.find(7, tree.head());
//     TEST(n == NULL);

//     n = tree.find(18, tree.head());
//     n->setLeft(new BNode<int>(11));
//     n->setRight(new BNode<int>(13));
//     cout << tree.toDot() << endl;
//     target = R"str(
// digraph G {
// graph [ordering="out"]
// "3" -> "8"
// "3" -> "12"
// "8" -> "2"
// "8" -> "18"
// "18" -> "11"
// "18" -> "13"
// "12" -> "5"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));

//     n = tree.find(3, tree.head());
//     n->setRight(new BNode<int>(4));
//     cout << tree.toDot() << endl;
//     target = R"str(
// digraph G {
// graph [ordering="out"]
// "3" -> "8"
// "3" -> "4"
// "8" -> "2"
// "8" -> "18"
// "18" -> "11"
// "18" -> "13"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));
//   }

//   {
//     BinaryTree<Person> tree;
//     tree.setHead(new BNode<Person>(Person("Theresa May", 55)));
//     tree.head()->setLeft(new BNode<Person>(Person("Tony Blair", 70)));
//     tree.head()->setRight(
//         new BNode<Person>(Person("Margaret Thatcher", 91)));
//     tree.head()->left()->setLeft(
//         new BNode<Person>(Person("Winston Churchill", 88)));
//     cout << tree.toDot() << endl;
//     string target = R"str(
// digraph G {
// graph [ordering="out"]
// "Theresa May 55" -> "Tony Blair 70"
// "Theresa May 55" -> "Margaret Thatcher 91"
// "Tony Blair 70" -> "Winston Churchill 88"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));

//   }

  const int numSuccesses = testNum - numFails;
  cout << numSuccesses << "/" << testNum << " tests succeeded" << endl;

  return numFails;
}

int main() {
  return runTests();
}

