#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class WordEntry {
private:
  // The word being stored
  string word;
  // The number of times this word has appeared
  int numAppearances;
  // The total accumulated score for this word
  int totalScore;

public:
  // Constructor: initializes the word with an initial score
  WordEntry(const string &, int);

  // Adds a new score for an appearance of the word and updates counters
  void addNewAppearance(int);

  // Returns the word string
  const string & getWord() const;

  // Calculates and returns the average score of the word
  double getAverage() const;
};
