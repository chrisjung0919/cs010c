#pragma once

#include <string>

using namespace std;

// A single node in the arithmetic expression tree.
// Each node holds a character (either operator or operand),
// a unique key (used for visualization), and pointers to left and right children.
struct TreeNode {
  char data;      // Operand or operator (e.g., 'a', '+')
  char key;       // Unique identifier for the node (e.g., 'a', 'b', 'c', ...)
  TreeNode* left; // Pointer to the left child
  TreeNode* right;// Pointer to the right child

  // Constructor initializes the data, key, and sets children to nullptr
  TreeNode(char data, char key)
    : data(data), key(key), left(nullptr), right(nullptr)
  {
  }
};

// Class that builds and operates on an arithmetic expression tree
class arithmeticExpression {
private:
  std::string infixExpression; // The original infix expression (e.g., "a+b*c")
  TreeNode* root;              // Root node of the expression tree

public:
  /* Constructor:
     Initializes an empty tree and sets the infixExpression
     to the value of parameter passed in. */
  arithmeticExpression(const string& expression);

  // Destructor:
  // Required by the Rule of Three.
  // Frees all memory allocated by the tree nodes.
  ~arithmeticExpression();

  // Rule of Three
   arithmeticExpression(const arithmeticExpression& other);
   arithmeticExpression& operator=(const arithmeticExpression& other);

  /* Converts the infixExpression to its equivalent postfix string
     and then generates the tree and assigns the root node to the 
     root data field. The key for the first node is 'a', 'b' for the second node and so on. */
  void buildTree();

  /* Calls the recursive infix function to print the expression in infix notation. */
  void infix() const;

  /* Calls the recursive prefix function to print the expression in prefix notation. */
  void prefix() const;

  /* Calls the recursive postfix function to print the expression in postfix notation. */
  void postfix() const;

private:
  /* Returns an integer based on the priority of the given operator.
     Higher value means higher precedence.
     Example: '*' and '/' have higher priority than '+' and '-' */
  static int priority(char);

  /* Converts the stored infixExpression to postfix (Reverse Polish Notation)
     using a stack-based algorithm. */
  string infix_to_postfix() const;

  /* Recursively prints the tree in infix notation (with parentheses)
     by performing an inorder traversal of the tree. */
  void infix(TreeNode* subtree) const;

  /* Recursively prints the tree in prefix notation
     by performing a preorder traversal of the tree. */
  void prefix(TreeNode* subtree) const;

  /* Recursively prints the tree in postfix notation
     by performing a postorder traversal of the tree. */
  void postfix(TreeNode* subtree) const;

  /* Recursively deletes all nodes in the tree
     by performing a postorder traversal. */
  void deleteTree(TreeNode* currentNode);
};
