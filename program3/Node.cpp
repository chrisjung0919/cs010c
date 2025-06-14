#include "Node.h"

// Default constructor: initializes with 1 data slot and null pointers
Node::Node()
  : numData(1),
    parent(nullptr),
    left(nullptr),
    middle(nullptr),
    right(nullptr)
{
}

// Constructor with one string value
Node::Node(const string& word )
  : small(word),
    numData(1),
    parent(nullptr),
    left(nullptr),
    middle(nullptr),
    right(nullptr)
{
}
