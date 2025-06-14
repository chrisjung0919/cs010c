#include <iostream>
#include "AVLTree.h"

using namespace std;

// Displays the menu and returns the user's choice
int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: " << endl;
  cout 
    << "1. Insert" << endl
    << "2. Print" << endl
    << "3. Quit" << endl;
  cin >> choice;

  // Clear input buffer in case of invalid input
  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}

int main() {
  AVLTree tree;  // Create an AVL tree object

  int choice = menu();  // Get initial menu choice
  string entry;

  while (choice != 3) {  // Loop until the user chooses to quit

    if (choice == 1) {
      // Insert a string into the tree
      cout << "Enter string to insert: ";
      getline(cin, entry);
      cout << endl;
      tree.insert(entry);

    } else if (choice == 2) {
      // Print the balance factors of all nodes in the tree
      tree.printBalanceFactors();
    }

    // Show menu again for next user choice
    choice = menu();
  }

  return 0;
}
