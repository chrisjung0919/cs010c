#pragma once
#include <string>

#include "Node.h"

class AVLTree {
  private:
    Node *root;
    void visualizeTree(const Node* subtree, int indent = 0) const;
    int height(Node* node) const;                   // Helper to compute height of a node
    Node* rebalance(Node* node);                    // Rebalance a node after insertion
    Node* insert(Node* node, const std::string&);   // Internal recursive insert helper
    void printBalanceFactors(Node* node) const;     // Internal in-order traversal printer
    void destroyTree(Node* node);                   // Helper to delete all nodes

  public:
    AVLTree();                                      // Constructor
    ~AVLTree();                                     // Destructor
    AVLTree(const AVLTree& other) = delete;         // Copy constructor (deleted)
    AVLTree& operator=(const AVLTree& other) = delete; // Copy assignment operator (deleted)

    void insert(const std::string&);                // Public insert
    int balanceFactor(Node*);                       // Compute balance factor
    void printBalanceFactors() const;               // Public print

    // Optional utility functions (not required but potentially useful)
    bool search(const std::string&); 
    std::string largest() const;
    std::string smallest() const;
    int height(const std::string&) const;
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;

    // Debugging utility to visualize the structure of the tree
    void visualizeTree() const { visualizeTree(root); }
};
