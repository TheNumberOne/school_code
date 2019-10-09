#include "./Heap.h"


#include <sstream>
// Provides floor, ceil, etc.
#include <cmath>
#include <assert.h>

using namespace std;

Heap::Heap() : A(0), arraySize(0), n(0) {}

// This assumes that every element of the array is an
// element of the heap.
Heap::Heap(Patient *inArray, int inArraySize, int inHeapSize) :
        A(static_cast<size_t>(inHeapSize)),
        arraySize(inHeapSize),
        n(inHeapSize) {
    std::copy(inArray, inArray + inHeapSize, A.data());
}

// Note: the function name is prefixed by Heap:: (the class
// name followed by two colons). Any function defined in
// the .cpp file must have this prefix.
const Patient &Heap::at(int i) const {
    return A[i];
}

Patient &Heap::at(int i) { return A[i]; }

bool Heap::operator==(const Heap &rhs) {
    if (n != rhs.n) return false;
    for (int i = 0; i < n; ++i) {
        if (A[i] != rhs.A[i]) return false;
    }
    return true;
}

bool Heap::operator==(const Patient *rhs) {
    for (int i = 0; i < n; ++i) {
        if (A[i] != rhs[i]) return false;
    }
    return true;
}

std::ostream &operator<<(std::ostream &out, const Heap &h) {
    out << "[";
    for (int i = 0; i < h.arraySize; ++i) {
        out << h.A[i];
        if (i < h.arraySize - 1) {
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
    while (true) {
        int l = left(i);
        int r = right(i);
        int max = i;
        if (l != -1 && A[l].priority() > A[max].priority()) max = l;
        if (r != -1 && A[r].priority() > A[max].priority()) max = r;
        if (max == i) return;
        using std::swap;
        swap(A[i], A[max]);
        i = max;
    }
}

void Heap::buildMaxHeap() {
    for (int i = parent(n - 1); i >= 0; i--) {
        maxHeapify(i);
    }
}

bool Heap::hasLeft(int i) const {
    return left(i) != -1;
}

bool Heap::hasRight(int i) const {
    return right(i) != -1;
}

void Heap::heapsort() {
    buildMaxHeap();
    using std::swap;
    while (n > 0) {
        swap(A[0], A[n - 1]);
        n--;
        maxHeapify(0);
    }
}

Patient Heap::extractMax() {
    assert(n > 0);
    Patient max = A[0];
    A[0] = A[n - 1];
    n--;
    maxHeapify(0);
    return max;
}

void Heap::insert(Patient patient) {
    if (n == arraySize) {
        size_t newSize = static_cast<size_t>(arraySize == 0 ? 4 : arraySize * 2);
        Array<Patient> newArr(newSize);
        std::copy(A.data(), A.data() + A.size(), newArr.data());
        A = newArr;
        arraySize = static_cast<int>(newSize);
    }
    A[n++] = patient;
    bubbleUp(n - 1);
}

const Patient &Heap::max() const {
    return A[0];
}

Patient &Heap::max() {
    return A[0];
}

void Heap::bubbleUp(int i) {
    while (true)
    {
        int p = parent(i);
        if (p < 0) return;
        if (A[p].priority() >= A[i].priority()) return;
        std::swap(A[p], A[i]);
        i = p;
    }
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
