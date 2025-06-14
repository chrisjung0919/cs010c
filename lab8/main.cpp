#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "HashTable.h"

using namespace std;

int main() {
	// Declare variables to store review lines, scores, and user input
	string line;
	int score;
	string message = " ";
	
	// Open the input file containing movie reviews
	ifstream myfile("movieReviews.txt");
	if (myfile.fail()) {
	    cout << "could not open file" << endl;
	    exit(1);
	}
	
	// Create a hash table with 20,071 buckets
	HashTable table(20071);
	
	// Read each review and insert words with their corresponding scores into the hash table
	while (true) {
	    myfile >> score;     // Read the score for the review
	    myfile.get();        // Consume the blank space after the score
	    getline(myfile, line); // Read the rest of the line (the review text)
	    if (not myfile) {
	      if (myfile.eof()) break; // End loop if end-of-file is reached
	      throw runtime_error("input failed");
	    }

	    // Process each word in the review line
	    int len = line.size();
	    while(len > 0) {
	        string sub;
	        len = line.find(" ");
	        if (len > 0) {
	            sub = line.substr(0, len); // Extract word before the space
	            line = line.substr(len + 1, line.size()); // Remove the processed word
	        }
	        else {
	            sub = line.substr(0, line.size() - 1); // Last word (or only one)
	        }
	        table.put(sub, score); // Add word and score to the hash table
	    }
	}
	
	// After the hash table is built, allow the user to enter new reviews
	while(message.length() > 0) {
	    cout << "enter a review -- Press return to exit: " << endl;
	    getline(cin, message);
	
	    // Variables for calculating the average sentiment score
	    double sum = 0;
	    int count = 0;
	    
	    double sentiment = 0.0;
	    
	    // Process the user-entered review word by word
	    size_t len = message.size();
	    while(len != string::npos) {
	        string sub;
	        len = message.find(" ");
	        if (len != string::npos) {
	            sub = message.substr(0, len); // Extract word before space
	            message = message.substr(len + 1, message.size()); // Remove word
	        }
	        else {
	            sub = message; // Last or only word
	        }

	        // Add the average score of the word to the sum
	        sum += table.getAverage(sub);
	        ++count;
	    }

	    // If the message is not empty, compute sentiment and display result
	    if (message.size() > 0) {
	    	sentiment = sum / count;
	        cout << "The review has an average value of " << sentiment << endl;
	        if (sentiment >= 3.0) {
	        	cout << "Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 2.0) {
	        	cout << "Somewhat Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 1.0) {
	        	cout << "Somewhat Negative Sentiment" << endl;
	        }
	        else {
	        	cout << "Negative Sentiment" << endl;
	        }
	        cout << endl;
	    }
	}
	
	return 0;
}
