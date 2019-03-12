#pragma once
// You should start by copying your BinaryTree project into here
// and modifying as necessary. Your BinarySearch tree will look
// something like
//
//    template <typename T, typename GetKey>
//    class BinarySearchTree {
//    };
//
// One of the data members will be
//
//    GetKey _getKey;

// Provides I/O
#include <iostream>
#include <string>

#include "./util.h"

/**
 * Represents a node in a binary tree
 */
template<typename T>
class BNode {
public:
    explicit BNode(T value) : m_data(value), m_left(nullptr), m_right(nullptr) {}

    const T &data() const { return m_data; }

    T &data() { return m_data; }

    void setData(T data) { m_data = data; }

    BNode<T> *left() const { return m_left; }

    void setLeft(BNode<T> *left) { m_left = left; }

    BNode<T> *right() const { return m_right; }

    void setRight(BNode<T> *right) { m_right = right; }

private:
    T m_data;
    BNode<T> *m_left;
    BNode<T> *m_right;
};


/**
 * Represents a binary search tree
 */
template<typename T, typename GetKey>
class BinarySearchTree {
public:
    typedef decltype(std::declval<GetKey>()(std::declval<T>())) KeyType;

    BinarySearchTree() = default;

    // Remove copy constructs to prevent memory leaks.
    BinarySearchTree(const BinarySearchTree<T, GetKey> &) = delete;

    BinarySearchTree<T, GetKey> &operator=(const BinarySearchTree<T, GetKey>) = delete;

    ~BinarySearchTree() {
        deleteTree(_head);
    }

    /**
     * Returns a pointer to the root node of the tree.
     */
    BNode<T> *head() const { return _head; }

    /**
     * Allows one to set the root node of the binary tree.
     * Takes ownership of the node and all of its children while releasing
     * ownership of the previous root node and children without deleting them.
     */
    void setHead(BNode<T> *head) { _head = head; }

    /**
     * Inserts the specified item into this BinarySearchTree
     */
    void insert(T item) {
        if (_head == nullptr) {
            setHead(new BNode<T>(item));
            return;
        }
        BNode<T> *node = _head;
        KeyType key = _getKey(item);
        while (true) {
            KeyType nodeKey = _getKey(node->data());

            if (key < nodeKey) {
                if (node->left() == nullptr) {
                    node->setLeft(new BNode<T>(item));
                    return;
                }

                node = node->left();
            } else if (nodeKey < key) {
                if (node->right() == nullptr) {
                    node->setRight(new BNode<T>(item));
                    return;
                }

                node = node->right();
            } else {
                node->setData(item);
                return;
            }
        }
    }

    /**
     * Returns the minimum value in this binary tree
     */
    const T &min() const {
        if (_head == nullptr) throw std::runtime_error("Tree is empty");
        BNode<T> *node = _head;
        while (node->left() != nullptr) {
            node = node->left();
        }
        return node->data();
    }

    /**
     * Returns the maximum value in this binary tree
     */
    const T &max() const {
        if (_head == nullptr) throw std::runtime_error("Tree is empty");
        BNode<T> *node = _head;
        while (node->right() != nullptr) {
            node = node->right();
        }
        return node->data();
    }

    /**
     * Finds the specified value under the specified root
     */
    BNode<T> *find(const T &value, BNode<T> *root) {
        if (root == nullptr) return nullptr;
        if (root->data() == value) return root;
        BNode<T> *ret = find(value, root->left());
        if (ret != nullptr) return ret;
        return find(value, root->right());
    }

    /**
     * Sees if this search tree contains the specified value. Returns false
     * if it contains an element with the same key that is not equivalent.
     */
    bool contains(const KeyType &value) const {
        return contains(_head, value);
    }

    /**
     * Returns the item with the specified key
     */
    const T &get(const KeyType &key) const {
        return get(_head, key);
    }

    /**
     * Returns the item with the specified key
     */
    T &get(const KeyType &key) {
        return const_cast<T &>(const_cast<const BinarySearchTree<T, GetKey> *>(this)->get(key));
    }

    /**
     * Copies the elements of this tree in order to the iterator.
     */
    template<typename Iter>
    void getInOrder(Iter out) const {
        int i = 0;
        getInOrder(_head, out);
    }

    std::string toDot() {
        using namespace std;
        string str = "digraph G {\n";
        str += "graph [ordering=\"out\"]\n";
        str += toDotNodes(_head);
        str += toDotImpl(_head);
        str += "}\n";
        return str;
    }

private:

    BNode<T> *_head = nullptr;
    GetKey _getKey;

    void deleteTree(BNode<T> *root) {
        if (root == nullptr) return;
        deleteTree(root->left());
        deleteTree(root->right());
        delete root;
    }

    std::string toDotImpl(BNode<T> *node) {
        using namespace std;
        if (!node) return "";
        string str;
        if (node->left()) {
            str += dotEdge(node->data(), node->left()->data());
        }
        if (node->right()) {
            str += dotEdge(node->data(), node->right()->data());
        }

        if (node->left()) {
            str += toDotImpl(node->left());
        }
        if (node->right()) {
            str += toDotImpl(node->right());
        }
        return str;
    }

    std::string toDotNodes(BNode<T> *node) {
        if (node == nullptr) return "";
        return toDotNodes(node->left()) + dotNode(node->data()) + toDotNodes(node->right());
    }

    bool contains(const BNode<T> *node, const KeyType &key) const {
        while (true) {
            if (node == nullptr) {
                return false;
            }

            if (key < _getKey(node->data())) {
                node = node->left();
            } else if (_getKey(node->data()) < key) {
                node = node->right();
            } else {
                return true;
            }
        }
    }

    const T &get(const BNode<T> *node, const KeyType &key) const {
        if (node == nullptr) throw std::runtime_error("Tree doesn't contain element with specified key.");

        if (key < _getKey(node->data())) {
            return get(node->left(), key);
        } else if (_getKey(node->data()) < key) {
            return get(node->right(), key);
        } else {
            return node->data();
        }
    }

    template<typename Iter>
    void getInOrder(const BNode<T> *tree, Iter &out) const {
        if (tree == nullptr) return;

        getInOrder(tree->left(), out);
        *(out++) = tree->data();
        getInOrder(tree->right(), out);
    }
};
