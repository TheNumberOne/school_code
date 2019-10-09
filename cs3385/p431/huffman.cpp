#include <sstream>
#include <algorithm>
#include <bits/unique_ptr.h>
#include <memory>

#include "./huffman.h"

const size_t NUM_CHARS = 1 << (8 * sizeof(char));

vector<CharFreq> characterFrequencies(const int *pInt);

void getCodewords(Node *root, string *codewords, const string &prefix);

void getCodewords(Node *root, string codewords[])
{
    getCodewords(root, codewords, "");
}

int ord(char c)
{
    return (int) (uint8_t) c;
}

char chr(int c)
{
    return (char) (uint8_t) c;
}

void getCodewords(Node *root, string *codewords, const string &prefix)
{
    if (root->left() == nullptr) {
        // Is leaf
        codewords[ord(root->data())] = prefix;
    } else {
        // Is stem
        getCodewords(root->left(), codewords, prefix + "0");
        getCodewords(root->right(), codewords, prefix + "1");
    }
}

Node *buildBinaryTree(const int *freq)
{
    return buildBinaryTree(characterFrequencies(freq));
}

vector<CharFreq> characterFrequencies(const int *pInt)
{
    vector<CharFreq> frequencies;
    
    for (int c = 0; c < NUM_CHARS; c++) {
        if (pInt[c] > 0) {
            frequencies.emplace_back(chr(c), pInt[c]);
        }
    }
    return frequencies;
}

bit_buffer &operator<<(bit_buffer &buffer, const string &code)
{
    for (char c : code) {
        if (c == '0') {
            buffer.add(0);
        } else {
            buffer.add(1);
        }
    }
    return buffer;
}

Node *buildBinaryTree(const vector<CharFreq> &chars)
{
    size_t n = chars.size();
    
    priority_queue<Node *, vector<Node *>, NodeComp> queue;
    
    for (const CharFreq &cf : chars) {
        queue.push(new Node(cf.f, cf.c));
    }
    
    for (int i = 1; i <= n - 1; i++) {
        Node *x = queue.top();
        queue.pop();
        Node *y = queue.top();
        queue.pop();
        Node *z = new Node(x->key() + y->key(), 0);
        z->left(x);
        z->right(y);
        queue.push(z);
    }
    return n == 0 ? nullptr : queue.top();
}

void countFrequencies(const string &data, int *freq)
{
    std::fill(freq, freq + NUM_CHARS, 0);
    for (char c : data) {
        freq[ord(c)]++;
    }
}

string getHeader(int *freq)
{
    std::stringstream ss;
    int numChars = 0;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) numChars++;
    }
    ss << numChars << std::endl;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            ss << i << " " << freq[i] << std::endl;
        }
    }
    return ss.str();
}

void deleteBinaryTree(Node *root)
{
    if (root == nullptr) return;
    deleteBinaryTree(root->left());
    deleteBinaryTree(root->right());
    delete root;
}

typedef std::unique_ptr<Node, decltype(&deleteBinaryTree)> unique_ptr_node;

unique_ptr_node make_unique_ptr_node(Node *ptr)
{
    return {ptr, &deleteBinaryTree};
}

string compressData(const string &data)
{
    auto frequencies = std::unique_ptr<int[]>(new int[NUM_CHARS]);
    countFrequencies(data, frequencies.get());
    
    auto tree = make_unique_ptr_node(buildBinaryTree(frequencies.get()));
    
    auto codewords = std::unique_ptr<string[]>(new string[NUM_CHARS]);
    getCodewords(tree.get(), codewords.get());
    
    std::stringstream ss;
    ss << getHeader(frequencies.get());
    
    bit_buffer buf;
    for (char c : data) {
        buf << codewords[ord(c)];
    }
    
    ss << buf;
    return ss.str();
}

char decode(bit_buffer &buffer, const Node *tree)
{
    while (tree->left() != nullptr) {
        int next = buffer.next();
        if (next == 0) {
            tree = tree->left();
        } else {
            tree = tree->right();
        }
    }
    // Is leaf
    return tree->data();
}

string uncompressData(const string &data)
{
    // Read frequencies from the header
    std::stringstream ss(data);
    int count;
    ss >> count;
    int freq[256];
    std::fill(freq, freq + 256, 0);
    for (int i = 0; i < count; ++i) {
        int c;
        int f;
        ss >> c >> f;
        freq[c] = f;
    }
    
    auto tree = make_unique_ptr_node(buildBinaryTree(freq));
    
    bit_buffer buf(ss);
    std::stringstream out;
    // TODO: Use the binary tree to get the characters back from the buffer.
    // Note that you should use the binary tree itself and not the
    // codewords to decompress the data.
    // Once you find the next character, add it to the output stream as
    //   out << c;
    while (buf.hasNext()) {
        out << decode(buf, tree.get());
    }
    
    return out.str();
}

