#include <iostream>
#include <sstream>
#include <stack>
#include <functional>

#include "arithmeticExpression.h"

using namespace std;

// Constructor: Initializes the object with the provided infix expression.
// The root of the tree is set to nullptr initially.
arithmeticExpression::arithmeticExpression(const string& expression)
  : infixExpression(expression), root(nullptr) {}

// Destructor: Recursively deletes all nodes in the tree to free memory.
arithmeticExpression::~arithmeticExpression() {
    deleteTree(root);
}

// Using function deleteTree used by the destructor
void arithmeticExpression::deleteTree(TreeNode* currentNode) {
    if (currentNode == nullptr) {
        return;
    }
    deleteTree(currentNode->left);
    deleteTree(currentNode->right);
    delete currentNode;
}

// Returns the priority level of an operator.
// Higher numbers mean higher precedence.
int arithmeticExpression::priority(char op) {
    int precedence = 0;
    if (op == '(') {
        precedence = 3;
    } else if (op == '*' || op == '/') {
        precedence = 2;
    } else if (op == '+' || op == '-') {
        precedence = 1;
    }
    return precedence;
}

// Converts the infix expression stored in infixExpression
// to postfix (Reverse Polish Notation) using a stack.
string arithmeticExpression::infix_to_postfix() const {
    stack<char> operatorStack;
    ostringstream postfixStream;
    char currentChar;

    for (unsigned i = 0; i < infixExpression.size(); ++i) {
        currentChar = infixExpression.at(i);

        // Skip spaces
        if (currentChar == ' ') {
            continue;
        }

        // If the character is an operator or parenthesis
        if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '(' || currentChar == ')') {
            if (currentChar == '(') {
                operatorStack.push(currentChar);
            } else if (currentChar == ')') {
                // Pop operators until the matching '('
                while (!operatorStack.empty() && operatorStack.top() != '(') {
                    postfixStream << operatorStack.top();
                    operatorStack.pop();
                }
                if (!operatorStack.empty()) {
                    operatorStack.pop(); // Remove '('
                }
            } else {
                // While there's an operator with greater or equal priority on top of the stack
                while (!operatorStack.empty() && priority(currentChar) <= priority(operatorStack.top())) {
                    if (operatorStack.top() == '(') {
                        break;
                    }
                    postfixStream << operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(currentChar);
            }
        } else {
            // If the character is an operand (like a, b, c, etc.)
            postfixStream << currentChar;
        }
    }

    // Pop any remaining operators from the stack
    while (!operatorStack.empty()) {
        postfixStream << operatorStack.top();
        operatorStack.pop();
    }

    return postfixStream.str();
}

// Builds the binary expression tree from the postfix expression.
// Uses a stack to assemble the tree bottom-up.
void arithmeticExpression::buildTree() {

    string postfix = infix_to_postfix();
    stack<TreeNode*> nodeStack;
    char uniqueKey = 'a'; // Unique key for each node (used for visualization)

    for (char currentChar : postfix) {
        if (isalnum(currentChar)) {
            // If it's an operand, create a node and push to stack
            nodeStack.push(new TreeNode(currentChar, uniqueKey++));
        } else {
            // It's an operator, so pop two nodes and make them children
            TreeNode* rightChild = nodeStack.top(); nodeStack.pop();
            TreeNode* leftChild = nodeStack.top(); nodeStack.pop();
            TreeNode* operatorNode = new TreeNode(currentChar, uniqueKey++);
            operatorNode->left = leftChild;
            operatorNode->right = rightChild;
            nodeStack.push(operatorNode);
        }
    }

    if (!nodeStack.empty()) {
        root = nodeStack.top(); // Final node is the root
    }
}

// Wrapper function: calls the private recursive infix printer
void arithmeticExpression::infix() const {
    infix(root);
}

// Recursive function to print the infix expression (with parentheses)
void arithmeticExpression::infix(TreeNode* currentNode) const {
    if (currentNode == nullptr) {
        return;
    }

    // Add parentheses for operators with both children
    if (currentNode->left != nullptr && currentNode->right != nullptr) {
        cout << "(";
    }

    infix(currentNode->left);            // Visit left subtree
    cout << currentNode->data;           // Visit root
    infix(currentNode->right);           // Visit right subtree

    if (currentNode->left != nullptr && currentNode->right != nullptr) {
        cout << ")";
    }
}

// Wrapper function: calls the private recursive prefix printer
void arithmeticExpression::prefix() const {
    prefix(root);
}

// Recursive function to print the prefix expression
void arithmeticExpression::prefix(TreeNode* currentNode) const {
    if (currentNode == nullptr) {
        return;
    }

    cout << currentNode->data;           // Visit root
    prefix(currentNode->left);           // Visit left subtree
    prefix(currentNode->right);          // Visit right subtree
}

// Wrapper function: calls the private recursive postfix printer
void arithmeticExpression::postfix() const {
    postfix(root);
}

// Recursive function to print the postfix expression
void arithmeticExpression::postfix(TreeNode* currentNode) const {
    if (currentNode == nullptr) {
        return;
    }

    postfix(currentNode->left);          // Visit left subtree
    postfix(currentNode->right);         // Visit right subtree
    cout << currentNode->data;           // Visit root
}
