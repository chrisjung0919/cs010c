#pragma once

#include <string>

// Node structure for AVL Tree
struct Node {
  std::string data;
  int count;
  Node* left;
  Node* right;
  Node(const std::string& data);
};
