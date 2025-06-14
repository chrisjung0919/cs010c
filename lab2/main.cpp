#include <iostream>
//Include IntList header file
#include "IntList.h"

using namespace std;

int main() {
  //Create empty list
  IntList list;
  
  //Call all functions and print them out

  cout << "empty: " << list << endl;
  cout << "list.empty() = " << list.empty() << endl;
  
  list.push_front(3);
  cout << "push front 3: " << list << endl;
  list.push_back(1);
  cout << "push back 1: " << list << endl;
  list.push_back(5);
  cout << "push back 5: " << list << endl;
  list.push_front(2);
  cout << "push front 2: " << list << endl;
  list.printReverse();
  cout << endl;

  list.pop_back();
  cout << "pop back: " << list << endl;
  list.pop_front();
  cout << "pop front: " << list << endl;
       

  list.printReverse();
  cout << endl;
  return 0;
}
