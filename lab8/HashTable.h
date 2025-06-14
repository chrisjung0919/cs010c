#pragma once

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class HashTable {

private:
  // Pointer to an array of lists, used for separate chaining to handle collisions
  list<WordEntry>* hashTable;
  // Total number of buckets in the hash table
  int size;

public:
  // Constructor that initializes the hash table with a given size
  HashTable(int size);

  // Destructor: deallocates dynamic memory to prevent leaks
  ~HashTable();

  // Disable copy constructor and assignment operator (Rule of Three)
  HashTable(const HashTable&) = delete;
  HashTable& operator=(const HashTable&) = delete;

  // Checks if a word exists in the hash table
  bool contains(const string& word) const;

  // Returns the average score of a given word
  double getAverage(const string& word) const;

  // Inserts a word with its score into the hash table, or updates it if already present
  void put(const string& word , int score);
 
private:
  // Computes the hash index for a given word
  int computeHash(const string&) const;
};
