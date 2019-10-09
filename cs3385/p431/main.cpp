//------------------------------------------------------------
//
// CS 3385
// Project p431
//
// In this project you will implement huffman codes for
// ASCII data compression. Understanding figure 16.5 of the
// textbook is critical to being able to do this assignment.
//
// Do not implement any functions in huffman.h. Leave the
// declarations in there and put your implementations in
// huffman.cpp.
//
// After your code passes all the tests, run the following:
//
//   ./project -c main.cpp test.huf
//
// Note to VisualStudio users: In VS 2008, 2010, 2012, 2013
// and 2015, right-click on the project, choose properties,
// and go to the Debugging section. There is a box for
// "Command Arguments" where you can enter -c, main.cpp and
// test.huf.
//
// This will use your code to compress main.cpp and put the
// results in test.huf. Note that the size of test.huf should
// be smaller than main.cpp. Then run
//
//   ./project -d test.huf test.cpp
//
// test.cpp should look identical to main.cpp.
//
// The final part of the assignment is to respond to a 
// secret question. Run the following:
//
//    ./project -d question.huf question.txt
//
// Read the secret question in question.txt, then respond
// by placing your answer in answer.txt and running
//
//    ./project -c answer.txt answer.huf
//
// Answering the question and compressing it correctly are
// worth 10% of the grade.
//
// Files to submit:
//   * huffman.h
//   * huffman.cpp
//   * answer.huf
// 
//------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <sstream>

#include "./util.h"
#include "./huffman.h"

using namespace std;

//------------------------------------------------------------
// Tests
//------------------------------------------------------------
int runTests()
{
    
    int numFails = 0;
    int testNum = 0;
    
    {
        // Visit huffman.h and follow the instructions for
        // getting a node class up and running. In this project
        // we will use the c++ standard template library (stl)
        // which has a priority_queue class, very similar to
        // the one we implemented in project p164. See below
        // for how to use priority_queue.
        priority_queue<Node *, vector<Node *>, NodeComp> queue;
        queue.push(new Node(45, 'a'));
        queue.push(new Node(13, 'b'));
        queue.push(new Node(12, 'c'));
        queue.push(new Node(16, 'd'));
        queue.push(new Node(9, 'e'));
        queue.push(new Node(5, 'f'));
        // Since our NodeComp class (in huffman.h) uses greater
        // than instead of less than, the priority queue
        // uses a min heap, putting the min key at the front
        // of the queue.
        TEST(queue.top()->data() == 'f');
        TEST(queue.top()->key() == 5);
        queue.pop();
        queue.pop();
        queue.pop();
        TEST(queue.top()->data() == 'b');
        TEST(queue.top()->key() == 13);
    }
    
    {
        // This code builds a character-frequency table
        // similar to what is shown on page 429 of the
        // textbook.
        int freq[256];
        std::fill(freq, freq + 256, 0); // Fill table with zeros
        freq['a'] = 45;
        freq['b'] = 13;
        freq['c'] = 12;
        freq['d'] = 16;
        freq['e'] = 9;
        freq['f'] = 5;
        
        // Using the character-frequency pairs, create a
        // binary tree using the Huffman algorithm on page 431
        // of the textbook. The easiest way to do this is to
        // initialize the leaf nodes (character-frequency pairs
        // from the table) as tiny binary trees that have
        // only a root, then combining the roots of the different
        // trees according to the algorithm. Note: do NOT add
        // characters with frequency zero.
        Node *root = buildBinaryTree(freq);
        
        // Get the codewords from the tree. A full traversal of
        // the tree is required to get all of the codewords.
        string codewords[256];
        getCodewords(root, codewords);
        TEST(codewords['a'] == "0");
        TEST(codewords['b'] == "101");
        TEST(codewords['c'] == "100");
        TEST(codewords['d'] == "111");
        TEST(codewords['e'] == "1101");
        TEST(codewords['f'] == "1100");
    }
    
    {
        int freq[256];
        std::fill(freq, freq + 256, 0);
        freq[' '] = 18;
        freq['!'] = 20;
        freq['('] = 1;
        freq['x'] = 13;
        freq['#'] = 33;
        freq['4'] = 444;
        
        Node *root = buildBinaryTree(freq);
        string codewords[256];
        getCodewords(root, codewords);
        TEST(codewords[' '] == "0111");
        TEST(codewords['!'] == "010");
        TEST(codewords['('] == "01100");
        TEST(codewords['x'] == "01101");
        TEST(codewords['#'] == "00");
        TEST(codewords['4'] == "1");
    }
    
    {
        string compressed =
            compressData("sssssssssssssssssssAssssssssssssssssssssssssss");
        TEST(compressed.size() == 22);
        string target = R"str(
 2
 65 1
 115 4
 )str";
        TEST(stringEquals(compressed.substr(0, 12), target));
        TEST((int) compressed[14] == 52);
        TEST((int) compressed[15] == 54);
        TEST((int) compressed[20] == -1);
        TEST((int) compressed[21] == -4);
    }
    
    {
        string compressed = compressData("Hello world!");
        TEST(compressed.size() == 60);
        string original = uncompressData(compressed);
        TEST(original == "Hello world!");
        TEST(original[0] == 'H');
        TEST(original[1] == 'e');
        TEST(original[2] == 'l');
        TEST(original[3] == 'l');
        TEST(original[4] == 'o');
        TEST(original[5] == ' ');
        TEST(original[6] == 'w');
        TEST(original[7] == 'o');
        TEST(original[8] == 'r');
        TEST(original[9] == 'l');
        TEST(original[10] == 'd');
        TEST(original[11] == '!');
    }
    
    const int numSuccesses = testNum - numFails;
    cout << numSuccesses << "/" << testNum << " tests succeeded" << endl;
    
    return numFails;
}

void modifyFile(const string &from, const string &to, const bool compress)
{
    // Check if we're going to overwrite the destination file
    {
        ifstream f(to, ios_base::in | ios_base::binary);
        if (f.good()) {
            cout << endl;
            cout << "***** Error *****" << endl;
            cout << to << " exists. Will not overwrite. Please delete the file "
                 << "and try again." << endl << endl;
            return;
        }
    }
    
    ifstream in(from);
    string str(
        static_cast<stringstream const &>(stringstream()
            << in.rdbuf()).str());
    in.close();
    
    string modified = compress ? compressData(str) : uncompressData(str);
    ofstream out(to);
    out << modified;
    out.close();
}

int main(int argc, char **argv)
{
    if (argc > 1) {
        modifyFile(argv[2], argv[3], string(argv[1]) == "-c");
        return 0;
    } else {
        return runTests();
    }
}

