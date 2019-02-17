#pragma once

// Provides I/O
#include <iostream>
#include <string>

#include "./util.h"

// TODO: add these functions to your BinaryTree class.
  // std::string toDotImpl(BNode<T>* node) {
  //   using namespace std;
  //   if (!node) return "";
  //   string str;
  //   if (node->left()) {
  //     str += dotEdge(node->data(), node->left()->data());
  //   }
  //   if (node->right()) {
  //     str += dotEdge(node->data(), node->right()->data());
  //   }

  //   if (node->left()) {
  //     str += toDotImpl(node->left());
  //   }
  //   if (node->right()) {
  //     str += toDotImpl(node->right());
  //   }
  //   return str;
  // }

  // std::string toDot() {
  //   using namespace std;
  //   string str = "digraph G {\n";
  //   str += "graph [ordering=\"out\"]\n";
  //   str += toDotImpl(_head);
  //   str += "}\n";
  //   return str;
  // }
