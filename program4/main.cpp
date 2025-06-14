#include <iostream>
#include <string>
#include "Jug.h"

using namespace std;

int main() {
    {
        // Variable to store the generated sequence of steps
        string solution;
        // Test case 1: jug A capacity 3, jug B capacity 5, goal is 4 gallons in B
        // Different operation costs
        Jug jugSolver(3, 5, 4, 1, 2, 3, 4, 5, 6);
        if (jugSolver.solve(solution) != 1) {
            cout << "Error 3" << endl;
        } else {
            cout << solution << endl << endl;
        }
    }

    {
        // Variable to store the generated sequence of steps
        string solution;
        // Test case 2: Same setup but with equal or lower costs
        Jug jugSolver(3, 5, 4, 1, 1, 1, 1, 1, 2);
        if (jugSolver.solve(solution) != 1) {
            cout << "Error 3" << endl;
        } else {
            cout << solution << endl;
        }
    }

    return 0;
}
