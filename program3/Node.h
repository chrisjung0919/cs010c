#pragma once

#include <string>

using std::string;

class Node {

  friend class Tree; // Tree can access Node's private members

private:
  string small;     // Smaller value
  string large;     // Larger value (if any)
  int numData;      // 1 or 2 values stored

  Node* parent;     // Pointer to parent
  Node* left;       // Left child
  Node* middle;     // Middle child
  Node* right;      // Right child (if two values)

public:
  Node(); // Default constructor

  // Prevents string-to-Node conversion
  explicit Node(const string& key);

};
