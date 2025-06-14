#include "AVLTree.h"
#include <iostream>
#include <algorithm>
using namespace std;

AVLTree::AVLTree() : root(nullptr) {}

// Destructor to clean up memory
AVLTree::~AVLTree() {
    destroyTree(root);
}

// Helper to delete all nodes in the tree using post-order traversal
void AVLTree::destroyTree(Node* currentNode) {
    if (!currentNode) return;
    destroyTree(currentNode->left);
    destroyTree(currentNode->right);
    delete currentNode;
}

// Compute the height of the subtree rooted at the given node
int AVLTree::height(Node* node) const {
    if (node == nullptr) return 0;
    return max(height(node->left), height(node->right)) + 1;
}

// Calculate balance factor: left subtree height - right subtree height
int AVLTree::balanceFactor(Node* node) {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

// Perform a right rotation around the given node
static Node* rotateRight(Node* unbalancedNode) {
    Node* newRoot = unbalancedNode->left;
    unbalancedNode->left = newRoot->right;
    newRoot->right = unbalancedNode;
    return newRoot;
}

// Perform a left rotation around the given node
static Node* rotateLeft(Node* unbalancedNode) {
    Node* newRoot = unbalancedNode->right;
    unbalancedNode->right = newRoot->left;
    newRoot->left = unbalancedNode;
    return newRoot;
}

// Rebalance the given node if it's unbalanced
Node* AVLTree::rebalance(Node* node) {
    int nodeBalanceFactor = balanceFactor(node);

    // Left-heavy
    if (nodeBalanceFactor > 1) {
        if (balanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left); // Convert to left-left case
        return rotateRight(node);
    }
    // Right-heavy
    else if (nodeBalanceFactor < -1) {
        if (balanceFactor(node->right) > 0)
            node->right = rotateRight(node->right); // Convert to right-right case
        return rotateLeft(node);
    }

    return node; // Already balanced
}

// Recursive helper to insert a value and maintain AVL properties
Node* AVLTree::insert(Node* node, const string& value) {
    if (!node) return new Node(value);

    if (value < node->data)
        node->left = insert(node->left, value);  // Insert into left subtree
    else if (value > node->data)
        node->right = insert(node->right, value); // Insert into right subtree
    else
        node->count++;  // Duplicate value, increment count

    return rebalance(node); // Ensure subtree is balanced after insertion
}

// Public insert function
void AVLTree::insert(const string& value) {
    root = insert(root, value);
}

// In-order traversal to print each node's balance factor
void AVLTree::printBalanceFactors(Node* node) const {
    if (!node) return;
    printBalanceFactors(node->left);
    cout << node->data << "(" << height(node->left) - height(node->right) << "), ";
    printBalanceFactors(node->right);
}

// Public function to print the balance factors
void AVLTree::printBalanceFactors() const {
    printBalanceFactors(root);
    cout << endl;
}

// Visualize the structure of the tree with indentation
void AVLTree::visualizeTree(const Node* subtree, int indent) const {
    for (int i = 0; i < indent; ++i) {
        cout << ' ';
    }

    if (subtree == nullptr) {
        cout << "-empty-" << endl;
    } else {
        cout << subtree->data << ' ' << '(' << (height(subtree->left) - height(subtree->right)) << ')' << endl;
        visualizeTree(subtree->left, indent + 4);
        visualizeTree(subtree->right, indent + 4);
    }
}
