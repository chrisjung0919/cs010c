#include "Tree.h"
#include <iostream>

using namespace std;

// Insert a new key into the tree
void Tree::insert(const string& key) {

    // Case 0: Tree is empty
    if (empty()) {
        root = new Node(key);
        return;
    }

    Node* insertNode = prepareOperation(key); // Find the node to insert the key into

    // Case 1: Key already exists
    if (insertNode->small == key || insertNode->large == key) {
        throw runtime_error("key already exists.");
    }

    // Case 2: Node has room for another key
    else if (insertNode->large.empty()) {
        insertNode->large = key;
        reorderTwoKeys(insertNode);  // Ensure keys are ordered correctly
    }

    // Case 3: Node is full; must split
    else {
        string keyToMoveUp = reorderThreeKeys(insertNode, key); // Determine which key goes up
        split(insertNode, keyToMoveUp);                         // Split node and move key up to parent
    }
}

// Remove a key from the tree
void Tree::remove(const string& key) {

    Node* victim = prepareOperation(key); // Locate node containing the key

    // Case 1: Key is in a leaf node
    if (!victim->left && !victim->middle && !victim->right) {

        // Key is the small key
        if (victim->small == key) {

            // Subcase: Node has only one key
            if (victim->large.empty()) { 

                // Sub-subcase: Node is root
                if (victim == root) {
                    delete root;
                    root = nullptr;
                }

                // Sub-subcase: Non-root node — must merge
                else {
                    merge(victim);
                }
            }

            // Subcase: Node has two keys — clear small key
            else { 
                victim->small.clear();
                reorderTwoKeys(victim);
            }
        }

        // Key is the large key
        else { 
            victim->large.clear();
        }
    }

    // Case 2: Key is in an internal node
    else {
        Node* successor; 
        if (victim->small == key) {
            successor = victim->middle;
        } else {
            successor = victim->right;
        }

        // Find in-order successor (leftmost in right subtree)
        while (successor->left) {
            successor = successor->left;
        }

        // Replace key with successor's small key
        if (victim->small == key) {
            victim->small = successor->small;
        } else {
            victim->large = successor->small;
        }
        reorderTwoKeys(victim);

        // Successor has one key — must merge
        if (successor->large.empty()) {
            merge(successor);
        }

        // Successor has two keys — remove small key
        else {
            successor->small.clear();
            reorderTwoKeys(successor);
        }    
    }
}

// Search for the existence of a key in the tree
bool Tree::search(const string& key) const {
    throw runtime_error("Haven't implemented search function");
    return false;
}

// Split a full node and promote a key to the parent
void Tree::split(Node* node, const string& keyToMoveUp) {

    Node* leftNode = new Node(node->small);    // Create new left node
    Node* rightNode = new Node(node->large);   // Create new right node
    Node* parent = node->parent;               // Get parent of current node

    // Case 1: Node is root — create new root
    if (node == root) {
        root = new Node(keyToMoveUp);
        root->left = leftNode;
        root->middle = rightNode;
        leftNode->parent = root;
        rightNode->parent = root;
    }

    // Case 2: Parent has room for a second key
    else if (parent->large.empty()) {
        parent->large = keyToMoveUp;
        parent->middle = leftNode;
        parent->right = rightNode;
        reorderTwoKeys(parent);
    }

    // Case 3: Parent is full — recursive split needed (not implemented)
    else if (!parent->large.empty()) {
        throw runtime_error("Haven't implemented recursive insert yet.");
    }

    delete node; // Clean up original node
}

// Merge node with sibling by pulling key down from parent
void Tree::merge(Node* node) {

    Node* parent = node->parent;

    // Case 1: Node is left child
    if (parent->left == node) {

        // Sibling has two keys — borrow one
        if (!parent->middle->large.empty()) {
            node->small = parent->small;
            parent->small = parent->middle->small;
            parent->middle->small.clear();
            reorderTwoKeys(parent->middle);
        }

        // Sibling has one key — merge node and sibling
        else {
            node->small = parent->small;
            node->large = parent->middle->small;
            parent->small.clear();
            parent->middle = nullptr;
            reorderTwoKeys(node);
            delete parent->middle;
        }
    }

    // Case 2: Node is middle child
    else if (parent->middle == node) {

        // Sibling has two keys — borrow one
        if (!parent->left->large.empty()) {
            node->small = parent->small;
            parent->small = parent->left->large;
            parent->left->large.clear();
        }

        // Sibling has one key — merge with sibling
        else {
            parent->left->large = parent->small;
            parent->small.clear();
            parent->middle = nullptr;
            delete node;
        }
    }

    // Case 3: Node is right child — not yet implemented
    else {
        throw runtime_error("Haven't implemented right child merge.");
    }

    // Special case: parent was root and now empty — make merged node new root
    if (parent == root && parent->small.empty() && parent->large.empty()) {
        root = parent->left;
        root->parent = nullptr;
        delete parent;
    }
}

// Ensure keys in a node are in ascending order
void Tree::reorderTwoKeys(Node* node) {

    // Only small key exists — nothing to do
    if (!node->small.empty() && node->large.empty()) return;

    // Large exists but small is empty — move large to small
    else if (node->small.empty() && !node->large.empty()) {
        node->small = node->large;
        node->large.clear();
    }

    // If out of order — swap keys
    else if (node->small > node->large) {
        const string changekey = node->small;
        node->small = node->large;
        node->large = changekey;
    }
}

// Reorder keys and return key to promote when splitting a full node
string Tree::reorderThreeKeys(Node* node, const string& key) {

    string keyToMoveUp = key;

    if (key < node->small) {
        keyToMoveUp = node->small;
        node->small = key;
    } 
    else if (key > node->large) {
        keyToMoveUp = node->large;
        node->large = key;
    }

    // If key is between small and large, it's the one to promote
    return keyToMoveUp;
}

// Traverse the tree to find the node containing (or closest to) the target key
Node* Tree::prepareOperation(const string& key) const {

    Node* curr = root;

    while (curr) {
        if (key < curr->small && curr->left) {
            curr = curr->left;
        } 
        else if (key > curr->small && (key < curr->large || curr->large.empty()) && curr->middle) {
            curr = curr->middle;
        } 
        else if (key > curr->large && curr->right) {
            curr = curr->right;
        } 
        else {
            return curr;
        }
    }

    throw runtime_error("key not found.");
}

// Recursively print keys in preorder traversal
void Tree::preOrder(Node* node) const {
    if (!node) return;

    cout << node->small << ", ";
    preOrder(node->left);

    if (!node->large.empty()) {
        cout << node->large << ", ";
    }

    preOrder(node->middle);
    preOrder(node->right);
}

// Recursively print keys in inorder traversal
void Tree::inOrder(Node* node) const {
    if (!node) return;

    inOrder(node->left);
    cout << node->small << ", ";
    inOrder(node->middle);

    if (!node->large.empty()) {
        cout << node->large << ", ";
    }

    inOrder(node->right);
}

// Recursively print keys in postorder traversal
void Tree::postOrder(Node* node) const {
    if (!node) return;

    postOrder(node->left);
    postOrder(node->middle);
    cout << node->small << ", ";
    postOrder(node->right);

    if (!node->large.empty()) {
        cout << node->large << ", ";
    }
}
