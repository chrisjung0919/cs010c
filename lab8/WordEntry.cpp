#include "WordEntry.h"
#include "WordEntry.h"

// WordEntry constructor
// Initializes a WordEntry object with the given word and score.
// Sets the initial number of appearances to 1 and stores the score.
WordEntry::WordEntry(const string &text, int score)
 : word(text), numAppearances(1), totalScore(score) {
	 
}

// addNewAppearance
// Adds a new score for the word.
// Increments the total score and the number of appearances.
void WordEntry::addNewAppearance(int s) {
	totalScore += s;
	++numAppearances;
}

// getWord
// Accessor function that returns the stored word.
// Used by HashTable for comparison and hashing.
const string & WordEntry::getWord() const {
    return word;
}

// getAverage
// Computes and returns the average score of the word.
// Typecasting is used to ensure floating-point division.
double WordEntry::getAverage() const {
	return static_cast<double>(totalScore) / numAppearances;
}
