#include "HashTable.h"
#include "WordEntry.h"

// Constructor for HashTable
// Initializes the hash table with the given size
// Each slot is a list of WordEntry objects (for collision handling via chaining)
HashTable::HashTable(int s) {
    size = s;
    hashTable = new list<WordEntry>[size];
}

// Destructor
// Deallocates the dynamically allocated array to prevent memory leaks.
HashTable::~HashTable() {
    delete[] hashTable;
}

// Hash function to compute an index from a string
// Uses the DJB2 algorithm for string hashing
// HashTable computeHash implementation assistance provided by ChatGPT, 
// which recommended and explained the use of the DJB2 hashing algorithm due to its simplicity, 
// efficiency, and effectiveness in distributing strings uniformly across buckets, minimizing collisions in the hash table.
int HashTable::computeHash(const string &s) const {
    unsigned long hash = 5381;
    for (int i = 0; i < s.length(); ++i) {
        hash = ((hash << 5) + hash) + s[i];  // hash * 33 + character
    }
    return hash % size;
}

// Inserts a word and its score into the hash table
// If the word exists, update its score and occurrence count
// If it does not exist, add it as a new WordEntry
// HashTable put assistance provided by ChatGPT, including guidance on handling collisions 
// using separate chaining with STL lists, iterating through existing entries to check for 
// duplicates, updating scores through the WordEntry interface, and inserting new entries when necessary.
void HashTable::put(const string &s, int score) {
    int index = computeHash(s);
    list<WordEntry>::iterator it;

    for (it = hashTable[index].begin(); it != hashTable[index].end(); ++it) {
        if (it->getWord() == s) {
            it->addNewAppearance(score);
            return;
        }
    }

    hashTable[index].push_back(WordEntry(s, score));
}

// Returns the average sentiment score of a word
// Returns 2.0 if the word is not found (neutral sentiment)
double HashTable::getAverage(const string &s) const {
    int index = computeHash(s);
    list<WordEntry>::const_iterator it;

    for (it = hashTable[index].begin(); it != hashTable[index].end(); ++it) {
        if (it->getWord() == s) {
            return it->getAverage();
        }
    }

    return 2.0;
}

// Checks if the hash table contains a specific word
// Returns true if found, false otherwise
bool HashTable::contains(const string &s) const {
    int index = computeHash(s);
    list<WordEntry>::const_iterator it;

    for (it = hashTable[index].begin(); it != hashTable[index].end(); ++it) {
        if (it->getWord() == s) {
            return true;
        }
    }

    return false;
}
