#include "./Heap.h"

#include <sstream>
// Provides floor, ceil, etc.
#include <cmath>

using namespace std;

Heap::Heap() : A(0), arraySize(0), n(0) {}

// This assumes that every element of the array is an
// element of the heap.
Heap::Heap(int *inArray, int inArraySize, int inHeapSize) :
        A(static_cast<size_t>(inHeapSize)),
        arraySize(inHeapSize),
        n(inHeapSize) {
    std::copy(inArray, inArray + inHeapSize, A.val);
}

// Note: the function name is prefixed by Heap:: (the class
// name followed by two colons). Any function defined in
// the .cpp file must have this prefix.
int Heap::at(int i) const {
    return A.val[i];
}

bool Heap::operator==(const Heap &rhs) {
    if (n != rhs.n) return false;
    for (int i = 0; i < n; ++i) {
        if (A.val[i] != rhs.A.val[i]) return false;
    }
    return true;
}

bool Heap::operator==(const int *rhs) {
    for (int i = 0; i < n; ++i) {
        if (A.val[i] != rhs[i]) return false;
    }
    return true;
}

std::ostream &operator<<(std::ostream &out, const Heap &h) {
    out << "[";
    for (int i = 0; i < h.n; ++i) {
        out << h.A.val[i];
        if (i < h.n - 1) {
            out << ", ";
        }
    }
    out << "]";
    return out;
}

int Heap::left(int i) const {
    if (i < 0) return -1;
    int left = i * 2 + 1;
    return left >= n ? -1 : left;
}

int Heap::right(int i) const {
    if (i < 0) return -1;
    int right = i * 2 + 2;
    return right >= n ? -1 : right;
}

int Heap::parent(int i) const {
    if (i >= n || i < 0) return -1;
    return (i - 1) / 2;
}

void Heap::maxHeapify(int i) {
    while (true)
    {
        int l = left(i);
        int r = right(i);
        int max = i;
        if (l != -1 && A[l] > A[max]) max = l;
        if (r != -1 && A[r] > A[max]) max = r;
        if (max == i) return;
        using std::swap;
        swap(A[i], A[max]);
        i = max;
    }
}

void Heap::buildMaxHeap() {
    for (int i = parent(n - 1); i>=0; i--) {
        maxHeapify(i);
    }
}

bool Heap::hasLeft(int i) const {
    return left(i) != -1;
}

bool Heap::hasRight(int i) const {
    return right(i) != -1;
}

string toDotImpl(const Heap &h, int i) {
    using namespace std;
    stringstream ss;
    if (h.hasLeft(i)) {
        ss << toDotImpl(h, h.left(i));
        ss << "\"" << h.at(i) << "\" -> \""
           << h.at(h.left(i)) << "\"\n";
    }
    if (h.hasRight(i)) {
        ss << toDotImpl(h, h.right(i));
        ss << "\"" << h.at(i) << "\" -> \""
           << h.at(h.right(i)) << "\"\n";
    }
    return ss.str();
}

string toDot(const Heap &h) {
    using namespace std;
    stringstream ss;
    ss << "digraph G {\n";
    ss << "graph [ordering=\"out\"]\n";
    ss << "\"" << h.at(0) << "\"\n";
    ss << toDotImpl(h, 0);
    ss << "}\n";
    return ss.str();
}
