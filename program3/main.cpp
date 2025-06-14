#define A "Aliens"
#define B "Clerks"
#define C "Die Hard"
#define D "Enemy of the State"
#define E "Gladiator"
#define F "Happy Gilmore"
#define G "Kill Bill Volume 1"
#define H "Kill Bill Volume 2"
#define I "Matrix"
#define J "Meet the Parents"
#define K "Pirates of the Caribbean"
#define L "Silence of the Lambs"
#define M "Spaceballs"
#define N "Star Wars"
#define O "Terminator"
#define P "The Lord of the Rings"
#define Q "The Usual Suspects"
#define R "Top Gun"


#include <iostream>
#include "Tree.h"

using namespace std;

// Print the tree in all 3 orders
void printOrders(Tree *tree) {
  cout << "Preorder = ";
  tree->preOrder( );
  cout << endl;
  cout << "Inorder = ";
  tree->inOrder( );
  cout << endl;
  cout << "Postorder = ";
  tree->postOrder( );
  cout << endl;
}

// Display menu and get user input
int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout 
    << "1. Insert" << endl
    << "2. Remove" << endl
    << "3. Print" << endl
    << "4. Search" << endl
    << "5. Quit" << endl;
  cin >> choice;

  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}

int main( ) {

  //Create the tree
  Tree tree;

  int choice = menu();

  string entry;
  
  while (choice != 5) {
    if (choice == 1) {
      cout << "Enter movie title to insert: ";
      getline(cin, entry);
      cout << endl;
      
      tree.insert(entry);
      
    } else if (choice == 2) {
      cout << "Enter movie title to remove: ";
      getline(cin, entry);
      cout << endl;
      
      tree.remove(entry);
      
    } else if (choice == 3) {
      printOrders(&tree);
      
    } else if (choice == 4) {
      cout << "Enter movie title to search for: ";
      getline(cin, entry);
      cout << endl;
      
      if (tree.search(entry)) {
        cout << "Found" << endl;
      } else {
        cout << "Not Found" << endl;
      }
    }

    choice = menu();
  }
  
  return 0;
}

