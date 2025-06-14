#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// The Node struct represents an individual player in the Josephus game.
// Each node contains a payload (the player's name) and a pointer to the next node.
struct Node {
    string payload;
    Node* next;
};

Node* newNode(const string& payload) {
  Node* node = new Node;      // Allocate memory for the new node
  node->payload = payload;    // Set the payload with the given string
  node->next = nullptr;       // Initialize the next pointer to nullptr
  return node;
}

// loadGame: Creates a circular linked list using the first n names from the provided vector.
// Each node in the list represents a player. Once all n nodes are added, the list is made circular
// by linking the last node back to the head.
Node* loadGame(int n, const vector<string>& names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) {
        name = names.at(i);
	// Special edge case when the list is initially empty
        if (head == nullptr) {
            head = newNode(name);
	          prev = head;
        } else {
            prev->next = newNode(name);
	          prev = prev->next;
        }
    }

  // Complete the circular linked list by setting the next pointer of the last node to the head.
    if (prev != nullptr) {
      prev->next = head;
    }
    return head;
}

// Print: Outputs the payload of each node in the circular linked list starting from 'start'.
void print(const Node* start) {
  const Node* curr = start;

  while (curr != nullptr) {
    cout << curr->payload << endl;
    curr = curr->next;
    if (curr == start) {
      break; // exit circular list
    }
  }
}

// josephus w circular list, k = num skips
//Simulates the Josephus elimination game on a circular linked list.
// Each round, the game skips k nodes and eliminates the kth node.
// The process continues until only one node (player) remains.
Node* runGame(Node* start, int k) {
  if (start == nullptr) return nullptr;

  Node* curr = start;
  Node* prev = curr;
  while (curr->next != curr) { // exit condition, last person standing


    for (int i = 0; i < k; ++i) { // find kth node
      prev = curr;
      curr = curr->next;
    }
    
    Node* next = curr->next;
    prev->next = next;
    delete curr;
    curr = next;
  }

  return curr; // last person standing
}

int main() {
  int n=1, k=1, max; // n = num names; k = num skips (minus 1)
  string name;
  vector<string> names;

  // get inputs
  cin >> n >> k;

  if (!cin) throw runtime_error("error reading n and k from input");
    
  while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

  // initialize and run game
  Node* startPerson = loadGame(n, names);
  Node* lastPerson = runGame(startPerson, k);

  // Declare the winner or report an error if the game failed.
  if (lastPerson != nullptr) {
    cout << lastPerson->payload << " wins!" << endl;
  } else {
    cout << "error: null game" << endl;
  }

  return 0;
}
