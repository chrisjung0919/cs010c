#include "Node.h"

#include <string>

// Constructor for the Node struct
// Left and right children are initialized to nullptr
Node::Node(const std::string& data)
  :data(data), count(1), left(nullptr), right(nullptr)
{
}
