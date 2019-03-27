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
class BNode
{
public:
    explicit BNode(T value) : _data(value), _left(nullptr), _right(nullptr) { }
    
    const T &data() const { return _data; }
    
    T &data() { return _data; }
    
    void data(T data) { _data = data; }
    
    BNode<T> *left() const noexcept { return _left; }
    
    void left(BNode<T> *left) noexcept { _left = left; }
    
    BNode<T> *right() const noexcept { return _right; }
    
    void right(BNode<T> *right) noexcept { _right = right; }

private:
    T _data;
    BNode<T> *_left;
    BNode<T> *_right;
};


/**
 * Represents a binary search tree
 */
template<typename T, typename GetKey>
class BinarySearchTree
{
public:
    typedef decltype(std::declval<GetKey>()(std::declval<T>())) KeyType;
    
    BinarySearchTree() = default;
    
    // Remove copy constructors to prevent memory leaks.
    BinarySearchTree(const BinarySearchTree<T, GetKey> &) = delete;
    
    BinarySearchTree<T, GetKey> &operator=(const BinarySearchTree<T, GetKey>&) = delete;
    
    ~BinarySearchTree()
    {
        deleteTree(_head);
    }
    
    /**
     * Inserts the specified item into this BinarySearchTree
     */
    void insert(T item)
    {
        BNode<T> *parent;
        BNode<T> *child;
        KeyType key = _getKey(item);
        std::tie(child, parent) = find_node(key);
        
        if (child != nullptr) {
            child->data(item);
        } else if (parent == nullptr) {
            _head = new BNode<T>(item);
        } else if (key < _getKey(parent->data())) {
            parent->left(new BNode<T>(item));
        } else {
            parent->right(new BNode<T>(item));
        }
    }
    
    /**
     * Returns the minimum value in this binary tree
     */
    const T &min() const
    {
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
    const T &max() const
    {
        if (_head == nullptr) throw std::runtime_error("Tree is empty");
        BNode<T> *node = _head;
        while (node->right() != nullptr) {
            node = node->right();
        }
        return node->data();
    }
    
    /**
     * Sees if this search tree contains the specified value. Returns false
     * if it contains an element with the same key that is not equivalent.
     */
    bool contains(const KeyType &key) const
    {
        const BNode<T> *_;
        const BNode<T> *node;
        std::tie(node, _) = find_node(key);
        return node != nullptr;
    }
    
    /**
     * Returns the item with the specified key
     */
    const T &get(const KeyType &key) const
    {
        const BNode<T> *_;
        const BNode<T> *node;
        std::tie(node, _) = find_node(key);
        if (node == nullptr) throw std::runtime_error("Item with specified key not in tree.");
        return node->data();
    }
    
    /**
     * Returns the item with the specified key
     */
    T &get(const KeyType &key)
    {
        return const_cast<T &>(const_cast<const BinarySearchTree<T, GetKey> *>(this)->get(key));
    }
    
    /**
     * Removes the item with the specified key from this tree. Does nothing if no item with they key exists.
     */
    void remove(const KeyType &key)
    {
        BNode<T> *parent;
        BNode<T> *toRemove;
        std::tie(toRemove, parent) = find_node(key);
        
        if (toRemove == nullptr) {
            return;
        }
        
        if (toRemove->left() == nullptr) {
            transplant(toRemove, parent, toRemove->right());
        } else if (toRemove->right() == nullptr) {
            transplant(toRemove, parent, toRemove->left());
        } else {
            BNode<T> *leftmostChild;
            BNode<T> *leftmostChildParent;
            std::tie(leftmostChild, leftmostChildParent) = find_min_node(toRemove->right(), toRemove);
            
            if (leftmostChildParent != toRemove) {
                transplant(leftmostChild, leftmostChildParent, leftmostChild->right());
                leftmostChild->right(toRemove->right());
            }
            transplant(toRemove, parent, leftmostChild);
            leftmostChild->left(toRemove->left());
        }
        
        delete toRemove;
    }
    
    /**
     * Copies the elements of this tree in order to the iterator.
     */
    template<typename Iter>
    void getInOrder(Iter out) const
    {
        int i = 0;
        getInOrder(_head, out);
    }
    
    std::string toDot()
    {
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
    
    void deleteTree(BNode<T> *root)
    {
        if (root == nullptr) return;
        deleteTree(root->left());
        deleteTree(root->right());
        delete root;
    }
    
    std::string toDotImpl(BNode<T> *node)
    {
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
    
    std::string toDotNodes(BNode<T> *node)
    {
        if (node == nullptr) return "";
        return toDotNodes(node->left()) + dotNode(node->data()) + toDotNodes(node->right());
    }
    
    template<typename Iter>
    void getInOrder(const BNode<T> *tree, Iter &out) const
    {
        if (tree == nullptr) return;
        
        getInOrder(tree->left(), out);
        *(out++) = tree->data();
        getInOrder(tree->right(), out);
    }
    
    /**
     * Finds the node and its parent with the given key. Returns null for the parent if the node
     * doesn't have a parent. Returns null for the node if the key isn't in the tree. Returns node
     * and parent in that order.
     */
    std::pair<BNode<T> *, BNode<T> *> find_node(const KeyType &key) const
    {
        BNode<T> *parent = nullptr;
        BNode<T> *node = _head;
        if (node == nullptr) {
            return {nullptr, nullptr};
        }
        
        while (true) {
            KeyType nodeKey = _getKey(node->data());
            BNode<T> *next;
            if (key < nodeKey) {
                if (node->left() == nullptr) {
                    return {nullptr, node};
                };
                next = node->left();
            } else if (nodeKey < key) {
                if (node->right() == nullptr) {
                    return {nullptr, node};
                }
                next = node->right();
            } else {
                return {node, parent};
            }
            parent = node;
            node = next;
        }
    }
    
    /**
     * Transplants the new child in the old child's place under the parent node.
     * Performs no deletion of objects.
     */
    void transplant(BNode<T> *oldChild, BNode<T> *parent, BNode<T> *newChild) noexcept
    {
        if (parent == nullptr) {
            _head = newChild;
        } else if (oldChild == parent->left()) {
            parent->left(newChild);
        } else {
            parent->right(newChild);
        }
    }
    
    /**
     * Finds the min node in the tree rooted at @param root. Returns that node and its parent.
     * Will return null for both values if @param root is null. Will return null if @param root is the min
     * node and @param rootParent is null. Returns node and parent in that order.
     */
    std::pair<BNode<T> *, BNode<T> *> find_min_node(BNode<T> *root, BNode<T> *rootParent) const
    {
        if (root == nullptr) return {nullptr, nullptr};
        
        while (true) {
            if (root->left() == nullptr) return {root, rootParent};
            rootParent = root;
            root = root->left();
        }
    }
};
