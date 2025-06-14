#include <exception>
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Creates and returns a vector of random lowercase characters ('a' to 'z')
vector<char> createVector() {
  int vectorSize = rand() % 26;
  char currentChar = 'a';
  vector<char> characterList;
  for(int index = 0; index < vectorSize; index++) {
    characterList.push_back(currentChar);
    currentChar++;
  }
  return characterList;
}

// Finds and returns the position of the smallest element in vals,
// considering elements from the specified start index through the end.
template<typename T>
unsigned min_index(const vector<T> &values, unsigned startIndex) {
  unsigned minIndex = startIndex;   // Assume current index holds min
  for (unsigned i = startIndex + 1; i < values.size(); ++i) {
      if (values[i] < values[minIndex]) {
          minIndex = i;
      }
  }
  return minIndex;
}

// Sorts the vector 'vals' in ascending order using selection sort
// Use min_index to find the index fo the min value
template<typename T>
void selection_sort(vector<T> &values) {
  unsigned totalElements = values.size();
  for (unsigned i = 0; i < totalElements; ++i) {
      unsigned minIndex = min_index(values, i);
      if (i != minIndex) {
          swap(values[i], values[minIndex]);
      }
  }
}

// Retrieves element at 'index' or throws out_of_range if invalid
template<typename T>
T getElement(const vector<T>& values, int elementIndex) {
  return values.at(elementIndex);
}

int main() {
  srand(time(0));

  // Int vector
  vector<int> intValues = {64, 25, 12, 22, 11};
  selection_sort(intValues);
  cout << "Sorted int vector: ";
  for(int elementIndex = 0; elementIndex < intValues.size(); elementIndex++){
    cout << intValues[elementIndex] << " ";
  }
  cout << endl;

  // Double vector
  vector<double> doubleValues = {64.5, 25.2, 12.7, 22.1, 11.9};
  selection_sort(doubleValues);
  cout << "Sorted double vector: ";
  for(size_t elementIndex = 0; elementIndex < doubleValues.size(); elementIndex++){
    cout << doubleValues[elementIndex] << " ";
  }
  cout << endl;

  // String vector
  vector<string> stringValues = {"banana", "apple", "cherry", "date"};
  selection_sort(stringValues);  // Sort the string vector in ascending order
  cout << "Sorted string vector: ";
  for(size_t elementIndex = 0; elementIndex < stringValues.size(); elementIndex++){
    cout << stringValues[elementIndex] << " ";
  }
  cout << endl;

  // Generate a random vector of characters ('a' to 'z')
  vector<char> randomChars = createVector();
  int numOfTries = 10;  // Number of attempts to get an element by index

  while(--numOfTries >= 0){
    cout << "Enter a number: " << endl;
    int userInputIndex;

    // Check if the input is a valid integer
    if (!(cin >> userInputIndex)) {
      throw runtime_error("could not read the index");
    }

    try {
      // Try to access the character at the given index
      char selectedChar = getElement(randomChars, userInputIndex);
      cout << "Element located at " << userInputIndex << ": is " << selectedChar << endl;
    } catch (const out_of_range &e) {
      // Catch and handle out-of-range errors
      cout << "out of range exception occured" << endl;
    }
  }

  return 0;
}
