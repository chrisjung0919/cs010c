//Include IntList header file
#include "IntList.h"

#include <iostream>

using std::ostream;

//Destructor for IntList
//Remove all node until the list is empty.
IntList::~IntList() {
  while (!empty()) {
    pop_front();
  }
}

//Push front function definition
void IntList::push_front(int value) {
  //New node used for push front
  IntNode* node = new IntNode(value);

  node->next = dummyHead.next;
  node->prev = &dummyHead;
  dummyHead.next->prev = node;
  dummyHead.next = node;
}

//Pop front function definition
void IntList::pop_front() {
  //If the list is empty return nothing.
  if(empty()){
    return;
  }

  //Set the target node to dummyHead next
  IntNode* nodeToRemove = dummyHead.next;
  dummyHead.next = nodeToRemove->next;
  nodeToRemove->next->prev = &dummyHead;

  delete nodeToRemove;
}

//Push back function definition
void IntList::push_back(int value) {
  //New node to push back
  IntNode* node = new IntNode(value);

  node->prev = dummyTail.prev;
  node->next = &dummyTail;
  dummyTail.prev->next = node;
  dummyTail.prev = node;
}

//Pop back function definition
void IntList::pop_back() {
  //If the list is empty return nothing.
  if(empty()){
    return;
  }

  //Set target node to previous of dummyTail
  IntNode* nodeToRemove = dummyTail.prev;
  dummyTail.prev = nodeToRemove->prev;
  nodeToRemove->prev->next = &dummyTail;

  //Delete the target (victim) at the end.
  delete nodeToRemove;
}

//Boolean IntList empty
bool IntList::empty() const {
  return dummyHead.next == &dummyTail;
}

//Operator for printing list from front to back
ostream & operator<<(ostream & out, const IntList &rhs){
  IntNode* current = rhs.dummyHead.next;

  while (current != &rhs.dummyTail) {
      out << current->data;
      current = current->next;
      if (current != &rhs.dummyTail) {
          out << " ";
      }
  }

  return out;
}

//Print Reverse function definition
void IntList::printReverse() const {
  //Current starts from previous of tail
  IntNode* current = dummyTail.prev;

  while (current != &dummyHead) {
  //Current goes previous and prints until it reach dummyHead.
      std::cout << current->data;
      current = current->prev;
      if (current != &dummyHead) {
          std::cout << " ";
      }
  }
}
