

#include <map>
#include <unordered_map>
#include "./DisjointSet.h"
#include "bmp.h"

class DisjointSet
{
public:
    DisjointSet() = default;
    
    void append(Node *n);
    
    Node *representative();
    
    size_t size() const;
    
    bool empty() const;
    
    void absorb(DisjointSet *other);

private:
    size_t _size = 0;
    Node *_head = nullptr;
    Node *_tail = nullptr;
};

void DisjointSet::append(Node *n)
{
    if (_head == nullptr) {
        _head = n;
    } else {
        _tail->_next = n;
    }
    n->_owner = this;
    n->_next = nullptr;
    _size++;
    _tail = n;
}

Node *DisjointSet::representative()
{
    return _head;
}

size_t DisjointSet::size() const
{
    return _size;
}

void DisjointSet::absorb(DisjointSet *other)
{
    if (this == other) return;
    if (other->empty()) return;
    
    if (empty()) {
        std::swap(_head, other->_head);
        std::swap(_tail, other->_tail);
        std::swap(_size, other->_size);
        return;
    }
    
    _tail->_next = other->_head;
    
    for (Node *n = other->_head; n != nullptr; n = n->_next) {
        n->_owner = this;
    }
    
    _tail = other->_tail;
    _size += other->_size;
    other->_size = 0;
}

bool DisjointSet::empty() const
{
    return _size == 0;
}


Node *makeSet()
{
    return makeSet(0);
}

Node *makeSet(int data)
{
    auto node = new Node(data);
    auto set = new DisjointSet();
    set->append(node);
    return node;
}

Node *find(Node *x)
{
    return x->_owner->representative();
}

// If the size of x's set is greater than or equal to the
// size of y's set, then merge y into x. Otherwise, merge x
// into y. This is the weighted union described in the
// video and book.
//
// After merging, be sure to delete one of the disjoint
// sets or you will have memory leaks. For example, if
// merging y into x, then after merging you would do
// something like
//     delete y->set();
// You do not need to delete any nodes, since they are
// simply transferred from one set to another.
//
// This function is called makeUnion() rather than just
// union() because union is a reserved word in C++.
//
void makeUnion(Node *x, Node *y)
{
    DisjointSet *a = x->_owner;
    DisjointSet *b = y->_owner;
    
    if (a == b) return;
    
    if (a->size() < b->size()) std::swap(a, b);
    a->absorb(b);
    delete b;
}

int Node::data() const
{
    return _data;
}

void Node::data(int data)
{
    _data = data;
}

void quantizeImage(
    const std::string &infile, const std::string &outfile, int numBins
)
{
    // Read the image
    Bitmap b;
    b.read(infile);
    
    // TODO: iterate through each pixel of the image. You can get the
    // dimensions of the image using b.width() and b.height(). You can
    // get a quantized version of a pixel using b.quantized(x,y,numBins).
    // You can write a new value to the pixel using b.setColor(x, y, c)
    // where c is an integer intensity.
    for (int x = 0; x < b.width(); x++) {
        for (int y = 0; y < b.height(); y++) {
            b.setColor(x, y, b.quantized(x, y, numBins));
        }
    }
    
    // Write the image
    b.write(outfile);
}

void connectedComponents(
    const std::string &infile, const std::string &outfile, int numBins
)
{
    // Read the file
    Bitmap b;
    b.read(infile);
    // Create a 2D array of nodes. The node pointers are not initialized.
    std::vector<std::vector<Node *>> nodes(
        (size_t) b.width(), std::vector<Node *>((size_t) b.height()));
    
    // TODO: initialize the node pointers, one for each pixel. The data
    // value for a node should be a value unique to all other nodes. For
    // a 4x4 image, this might be
    //   0  1  2  3
    //   4  5  6  7
    //   8  9 10 11
    //  12 13 14 15
    // Do not use the quantized pixel intensity for the node data value.
    for (int x = 0; x < b.width(); x++) {
        for (int y = 0; y < b.height(); y++) {
            nodes[x][y] = makeSet(y * b.width() + x);
        }
    }
    
    std::vector<int> quantized((size_t) b.width() * b.height());
    
    // quantizing is an expensive operation so we do it in one pass,
    for (int x = 0; x < b.width(); x++) {
        for (int y = 0; y < b.height(); y++) {
            quantized[y * b.width() + x] = b.quantized(x, y, numBins);
        }
    }
    
    // TODO: Follow the algorithm you wrote in the homework to find
    // connected components. You will use b.quantized(x, y, numBins)
    // to get the pixel intensity.
    for (int x = 0; x < b.width(); x++) {
        for (int y = 0; y < b.height(); y++) {
            int q = quantized[y * b.width() + x];
            if (x != 0 && q == quantized[y * b.width() + x - 1]) {
                makeUnion(nodes[x][y], nodes[x - 1][y]);
            }
            if (y != 0 && q == quantized[(y - 1) * b.width() + x]) {
                makeUnion(nodes[x][y], nodes[x][y - 1]);
            }
        }
    }
    
    // TODO: Overwrite the image giving each connected component a unique
    // color. Each connected component should have a unique ID in the
    // representative node's data(). Use this integer ID to get a unique
    // color using the following code:
    //    Color c = Color::createRandom(id);
    // You can then set the pixel's color in the image using
    //    b.setColor(x, y, c);
    // creating colors is an expensive operation so we
    std::unordered_map<int, Color> colors{ };
    for (int x = 0; x < b.width(); x++) {
        for (int y = 0; y < b.height(); y++) {
            int id = find(nodes[x][y])->data();
            auto location = colors.find(id);
            if (location == colors.end()) {
                location = colors.emplace(id, Color::createRandom(id)).first;
            }
            b.setColor(x, y, location->second);
        }
    }
    
    // Write the image
    b.write(outfile);
}