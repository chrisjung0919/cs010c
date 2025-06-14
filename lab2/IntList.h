#pragma once

#include <iostream>

//Struct for doubly-linked list
struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    //IntNode constructor
    IntNode(int data) : data(data), prev(nullptr), next(nullptr) {}
};

class IntList {
private:
  //DummyHead and DummyTail node
  IntNode dummyHead;
  IntNode dummyTail;

public:
  //IntList constructor
  IntList()
    : dummyHead(-1),
      dummyTail(-1)
  {
    // The dummy head points to dummy tail
    dummyHead.prev = nullptr;
    dummyHead.next = &dummyTail;

    // The dummy tail points back at head
    dummyTail.prev = &dummyHead;
    dummyTail.next = nullptr;
  }

  ~IntList();
  IntList(const IntList&) = delete;  // Don't let C++ write these for you
  IntList& operator=(const IntList&) = delete;

  // Inserts a data value (within a new node) at the front end of the
  // list.
  // This must be an O(1) operation.
  void push_front(int value);

  // Removes the node at the front end of the list (the node after
  // the dummy head). Does nothing if the list is already empty.
  // This must be an O(1) operation.
  void pop_front();

  // Inserts a data value (within a new node) at the back end of the
  // list.
  // This must be an O(1) operation.
  void push_back(int value);

  // Removes the node at the back end of the list (the node before
  // the dummy tail). Does nothing if the list is already empty.
  // This must be an O(1) operation.
  void pop_back();

  //  Returns true if the list does not store any data values (it
  // only has dummy head and dummy tail), otherwise returns false.
  bool empty() const;

  // A global friend function that outputs to the stream all of the
  // by a space. This function does NOT send to the stream a newline
  // or space at the end.
  // Note the use of std::ostream.  It is VERY bad practice to put
  // `using namespace XXXX;` in a header file
  friend std::ostream & operator<<(std::ostream &out, const IntList &rhs);

  // This function does NOT send to the stream a newline
  // or space at the end.
  void printReverse() const;
};
