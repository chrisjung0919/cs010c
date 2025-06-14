#include "BSTree.h"
#include <iostream>

// PUBLIC FUNCTIONS

// Insert a new key into the BST
void BSTree::insert(const std::string& key) {
    if (root == nullptr) {
        root = new Node(key);
        return;
    }

    Node* curr = root;
    while (curr != nullptr) {
        if (key == curr->key) {
            // Key already exists; increment the count
            curr->count++;
            return;
        } else if (key < curr->key) {
            // Move to the left subtree
            if (curr->left == nullptr) {
                curr->left = new Node(key);
                return;
            } else {
                curr = curr->left;
            }
        } else {
            if (curr->right == nullptr) {
                // Move to the right subtree
                curr->right = new Node(key);
                return;
            } else {
                curr = curr->right;
            }
        }
    }
}

// Search for a key in the BST
bool BSTree::search(const std::string& key) const {
    Node* curr = root;
    while (curr != nullptr) {
        if (key == curr->key) {
            return true;
        } else if (key < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return false;
}

// Find and return the largest key in the BST
std::string BSTree::largest() const {
    if (root == nullptr) {
        return "";
    }
    Node* curr = root;
    while (curr->right != nullptr) {
        curr = curr->right;
    }
    return curr->key;
}

// Find and return the smallest key in the BST
std::string BSTree::smallest() const {
    if (root == nullptr) {
        return "";
    }
    Node* curr = root;
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr->key;
}

// Find the height of the node with given key
int BSTree::height(const std::string& key) const {
    Node* curr = root;
    while (curr != nullptr) {
        if (key == curr->key) {
            return height_of(curr);
        } else if (key < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return -1;
}

// Remove a key from the BST
void BSTree::remove(const std::string& key) {
    remove(nullptr, root, key);
}

// Print the BST in preorder traversal
void BSTree::preOrder() const {
    preOrder(root);
    std::cout << std::endl;
}

// Print the BST in inorder traversal
void BSTree::inOrder() const {
    inOrder(root);
    std::cout << std::endl;
}

// Print the BST in postorder traversal
void BSTree::postOrder() const {
    postOrder(root);
    std::cout << std::endl;
}

// PRIVATE RECURSIVE HELPERS

// Helper function to find height of a subtree rooted at a given node
int BSTree::height_of(Node* tree) const {
    if (tree == nullptr) {
        return -1;
    }
    int leftHeight = height_of(tree->left);
    int rightHeight = height_of(tree->right);
    return 1 + std::max(leftHeight, rightHeight);
}

// Helper function to traverse and print tree in preorder
void BSTree::preOrder(Node* tree) const {
    if (tree == nullptr) {
        return;
    }
    std::cout << tree->key << "(" << tree->count << "), ";
    preOrder(tree->left);
    preOrder(tree->right);
}

// Helper function to traverse and print tree in inorder
void BSTree::inOrder(Node* tree) const {
    if (tree == nullptr) {
        return;
    }
    inOrder(tree->left);
    std::cout << tree->key << "(" << tree->count << "), ";
    inOrder(tree->right);
}

// Helper function to traverse and print tree in postorder
void BSTree::postOrder(Node* tree) const {
    if (tree == nullptr) {
        return;
    }
    postOrder(tree->left);
    postOrder(tree->right);
    std::cout << tree->key << "(" << tree->count << "), ";
}

// Helper function to remove a node from the BST
void BSTree::remove(Node* parent, Node* tree, const std::string& key) {
    // Nothing in tree
    if (tree == nullptr) {
        return;
    }
    if (key < tree->key) {
        remove(tree, tree->left, key);
    } else if (key > tree->key) {
        remove(tree, tree->right, key);
    } else { // Found the node
        if (tree->count > 1) {
            tree->count--;
            return;
        }
        if (tree->left == nullptr && tree->right == nullptr) {
            // Both left and right are nullptr
            if (parent == nullptr) {
                root = nullptr;
            } else if (parent->left == tree) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            // delete tree
            delete tree;
        } else if (tree->left != nullptr) {
            Node* maxLeftParent = tree;
            Node* maxLeft = tree->left;
            while (maxLeft->right != nullptr) {
                maxLeftParent = maxLeft;
                maxLeft = maxLeft->right;
            }
            tree->key = maxLeft->key;
            tree->count = maxLeft->count;
            maxLeft->count = 1; // Force count to 1 before removing donor
            remove(maxLeftParent, maxLeft, maxLeft->key);
        } else {
            Node* minRightParent = tree;
            Node* minRight = tree->right;
            while (minRight->left != nullptr) {
                minRightParent = minRight;
                minRight = minRight->left;
            }
            tree->key = minRight->key;
            tree->count = minRight->count;
            minRight->count = 1; // Force count to 1 before removing donor
            remove(minRightParent, minRight, minRight->key);
        }
    }
}
