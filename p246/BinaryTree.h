#pragma once

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
 * Represents a binary tree
 */
template<typename T>
class BinaryTree {

public:
    ~BinaryTree() {
        deleteTree(m_head);
    }

    /**
     * Returns a pointer to the root node of the tree.
     */
    BNode<T> *head() const { return m_head; }

    /**
     * Allows one to set the root node of the binary tree.
     * Takes ownership of the node and all of its children while releasing
     * ownership of the previous root node and children without deleting them.
     */
    void setHead(BNode<T> *head) { m_head = head; }

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

    std::string toDot() {
        using namespace std;
        string str = "digraph G {\n";
        str += "graph [ordering=\"out\"]\n";
        str += toDotImpl(m_head);
        str += "}\n";
        return str;
    }

private:
    BNode<T> *m_head = nullptr;

    void deleteTree(BNode<T> *root) {
        if (root == nullptr) return;
        deleteTree(root->left());
        deleteTree(root->right());
        delete root;
    }
};
