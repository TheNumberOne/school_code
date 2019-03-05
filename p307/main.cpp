//------------------------------------------------------------
//
// CS 3385
// Project p307
//
// In this project you will build a binary search tree.
//
// Start by copying your code over from the binary tree
// project.
//
// You will want to keep both the key and the data in the
// binary tree node. Also add a pointer to the parent.
//
// You can visualize your tree by calling toDot() and then
// plugging the result in to www.webgraphviz.com. Modify the
// toDot() from the binary tree to include printing out
// nodes. The nodes are printed using an in-order traversal.
// For example, if your tree has only a root with
// value 8, then toDot() would return
//    digraph G {
//    graph [ordering="out"]
//    "8"
//    }
//
// If you add 3 then toDot() would return
//    digraph G {
//    graph [ordering="out"]
//    "3"
//    "8"
//    "8" -> "3"
//    }
//
// And adding a 12...
//    digraph G {
//    graph [ordering="out"]
//    "3"
//    "8"
//    "12"
//    "8" -> "3"
//    "8" -> "12"
//    }
//
// To add nodes to your graphviz dot representation you
// could rename toDotImpl() to toDotEdges() and add an additional
// function: toDotNodes().
//
// Be sure to use the code checker (linked to from the syllabus
// web page) to make sure your code will work when graded!
//
// File to submit:
//   * BinarySearchTree.h
// 
//------------------------------------------------------------

#include <iostream>
#include <sstream>

#include "./util.h"
#include "./Student.h"
#include "./BinarySearchTree.h"

using namespace std;

class Identity {
 public:
  int operator()(const int i) {
    return i;
  }
};
class GetId {
 public:
  int operator()(const Student& s) {
    return s.id();
  }
};
class GetAge {
 public:
  int operator()(const Student& s) {
    return s.age();
  }
};

//------------------------------------------------------------
// Tests
//------------------------------------------------------------
int runTests() {

  int numFails = 0;
  int testNum = 0;

//   {
//     BinarySearchTree<int, Identity> tree;
//     string target = R"str(
// digraph G {
// graph [ordering="out"]
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));

//     tree.insert(8);
//     target = R"str(
// digraph G {
// graph [ordering="out"]
// "8"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));

//     tree.insert(3);
//     target = R"str(
// digraph G {
// graph [ordering="out"]
// "3"
// "8"
// "8" -> "3"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));

//     tree.insert(12);
//     target = R"str(
// digraph G {
// graph [ordering="out"]
// "3"
// "8"
// "12"
// "8" -> "3"
// "8" -> "12"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));

//     tree.insert(15);
//     target = R"str(
// digraph G {
// graph [ordering="out"]
// "3"
// "8"
// "12"
// "15"
// "8" -> "3"
// "8" -> "12"
// "12" -> "15"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));
//   }

//   {
//     BinarySearchTree<int, Identity> tree;
//     tree.insert(12);
//     tree.insert(8);
//     tree.insert(15);
//     tree.insert(3);
//     string target = R"str(
// digraph G {
// graph [ordering="out"]
// "3"
// "8"
// "12"
// "15"
// "12" -> "8"
// "12" -> "15"
// "8" -> "3"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));
//   }

//   {
//     BinarySearchTree<int, Identity> tree;
//     tree.insert(3);
//     tree.insert(8);
//     tree.insert(15);
//     tree.insert(12);
//     string target = R"str(
// digraph G {
// graph [ordering="out"]
// "3"
// "8"
// "12"
// "15"
// "3" -> "8"
// "8" -> "15"
// "15" -> "12"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));
//   }

//   {
//     BinarySearchTree<int, Identity> tree;
//     tree.insert(8);
//     tree.insert(4);
//     tree.insert(12);
//     tree.insert(2);
//     tree.insert(6);
//     tree.insert(10);
//     tree.insert(14);
//     tree.insert(1);
//     tree.insert(3);
//     tree.insert(5);
//     tree.insert(7);
//     tree.insert(9);
//     tree.insert(11);
//     tree.insert(13);
//     tree.insert(15);
//     string target = R"str(
// digraph G {
// graph [ordering="out"]
// "1"
// "2"
// "3"
// "4"
// "5"
// "6"
// "7"
// "8"
// "9"
// "10"
// "11"
// "12"
// "13"
// "14"
// "15"
// "8" -> "4"
// "8" -> "12"
// "4" -> "2"
// "4" -> "6"
// "2" -> "1"
// "2" -> "3"
// "6" -> "5"
// "6" -> "7"
// "12" -> "10"
// "12" -> "14"
// "10" -> "9"
// "10" -> "11"
// "14" -> "13"
// "14" -> "15"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));
//   }

//   {
//     BinarySearchTree<int, Identity> tree;
//     tree.insert(8);
//     tree.insert(4);
//     tree.insert(10);
//     tree.insert(14);
//     tree.insert(12);
//     tree.insert(2);
//     tree.insert(1);
//     tree.insert(6);
//     tree.insert(11);
//     tree.insert(5);
//     tree.insert(7);
//     tree.insert(9);
//     tree.insert(3);
//     tree.insert(13);
//     tree.insert(15);
//     string target = R"str(
// digraph G {
// graph [ordering="out"]
// "1"
// "2"
// "3"
// "4"
// "5"
// "6"
// "7"
// "8"
// "9"
// "10"
// "11"
// "12"
// "13"
// "14"
// "15"
// "8" -> "4"
// "8" -> "10"
// "4" -> "2"
// "4" -> "6"
// "2" -> "1"
// "2" -> "3"
// "6" -> "5"
// "6" -> "7"
// "10" -> "9"
// "10" -> "14"
// "14" -> "12"
// "14" -> "15"
// "12" -> "11"
// "12" -> "13"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));
//   }

//   {
//     BinarySearchTree<int, Identity> tree;
//     tree.insert(8);
//     tree.insert(4);
//     tree.insert(10);
//     // Use the following function signature:
//     //     T min() {
//     //       ...
//     //     }
//     TEST(tree.min() == 4);
//     TEST(tree.max() == 10);
//   }

//   {
//     BinarySearchTree<int, Identity> tree;
//     tree.insert(11);
//     tree.insert(7);
//     tree.insert(5);
//     TEST(tree.min() == 5);
//     TEST(tree.max() == 11);
//   }

//   {
//     BinarySearchTree<int, Identity> tree;
//     tree.insert(11);
//     tree.insert(7);
//     tree.insert(5);
//     TEST(tree.contains(11));
//     TEST(tree.contains(7));
//     TEST(tree.contains(5));
//     TEST(!tree.contains(1));
//     TEST(!tree.contains(6));

//     TEST(tree.get(11) == 11);
//     TEST(tree.get(7) == 7);
//     TEST(tree.get(5) == 5);
//   }

//   {
//     // Use GetId as the getKey function so that nodes
//     // will be ordered by student ID.
//     BinarySearchTree<Student, GetId> tree;
//     tree.insert(Student("Joe", 587, 21));
//     tree.insert(Student("Sally", 223, 22));
//     tree.insert(Student("Kylie", 982, 20));
//     tree.insert(Student("Josh", 363, 35));
//     string target = R"str(
// digraph G {
// graph [ordering="out"]
// "Sally 223 22"
// "Josh 363 35"
// "Joe 587 21"
// "Kylie 982 20"
// "Joe 587 21" -> "Sally 223 22"
// "Joe 587 21" -> "Kylie 982 20"
// "Sally 223 22" -> "Josh 363 35"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));

//     TEST(tree.contains(587));
//     TEST(tree.contains(223));
//     TEST(tree.contains(982));
//     TEST(!tree.contains(21));
//     TEST(!tree.contains(22));

//     TEST(tree.get(587).name() == "Joe");
//     TEST(tree.get(223).name() == "Sally");

//     // Inserts elements in order into array. Students should
//     // be ordered by student ID.
//     Student students[4];
//     tree.getInOrder(students);
//     printArray(students, 4);
//     TEST(students[0].name() == "Sally");
//     TEST(students[1].name() == "Josh");
//     TEST(students[2].name() == "Joe");
//     TEST(students[3].name() == "Kylie");
//   }

//   {
//     // Use GetAge as the getKey function so that nodes
//     // will be ordered by age.
//     BinarySearchTree<Student, GetAge> tree;
//     tree.insert(Student("Joe", 587, 21));
//     tree.insert(Student("Sally", 223, 22));
//     tree.insert(Student("Kylie", 982, 20));
//     tree.insert(Student("Josh", 363, 35));
//     string target = R"str(
// digraph G {
// graph [ordering="out"]
// "Kylie 982 20"
// "Joe 587 21"
// "Sally 223 22"
// "Josh 363 35"
// "Joe 587 21" -> "Kylie 982 20"
// "Joe 587 21" -> "Sally 223 22"
// "Sally 223 22" -> "Josh 363 35"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));

//     TEST(!tree.contains(587));
//     TEST(!tree.contains(223));
//     TEST(!tree.contains(982));
//     TEST(tree.contains(21));
//     TEST(tree.contains(22));

//     TEST(tree.get(21).name() == "Joe");
//     TEST(tree.get(22).name() == "Sally");

//     Student students[4];
//     tree.getInOrder(students);
//     printArray(students, 4);
//     TEST(students[0].name() == "Kylie");
//     TEST(students[1].name() == "Joe");
//     TEST(students[2].name() == "Sally");
//     TEST(students[3].name() == "Josh");
//   }

//   {
//     BinarySearchTree<int, Identity> tree;
//     tree.insert(11);
//     tree.insert(7);
//     tree.insert(5);
//     tree.insert(18);
//     tree.insert(12);
//     tree.remove(5);
//     TEST(!tree.contains(5));

//     string target = R"str(
// digraph G {
// graph [ordering="out"]
// "7"
// "11"
// "12"
// "18"
// "11" -> "7"
// "11" -> "18"
// "18" -> "12"
// }
// )str";
//     TEST(stringEquals(tree.toDot(), target));

//     tree.insert(13);
//     tree.insert(19);
//     tree.insert(4);
//     tree.insert(10);
//     tree.remove(11);
//     TEST(!tree.contains(11));

//     target = R"str(
// digraph G {
// graph [ordering="out"]
// "4"
// "7"
// "10"
// "12"
// "13"
// "18"
// "19"
// "12" -> "7"
// "12" -> "18"
// "7" -> "4"
// "7" -> "10"
// "18" -> "13"
// "18" -> "19"
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

