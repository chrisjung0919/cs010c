#ifndef JUG_H
#define JUG_H

#include <string>
#include <queue>
#include <vector>
#include <set>

class Jug {
public:
    // Constructor: initializes jug capacities, goal amount, and all operation costs
    Jug(int jugACap, int jugBCap, int goal, int costFillA, int costFillB,
        int costEmptyA, int costEmptyB, int costPourAB, int costPourBA);

    // Destructor: provided for rule of three
    ~Jug();

    // Solves the jug problem and generates the cheapest sequence of steps
    // Returns -1 for invalid input, 0 for no solution, and 1 for a valid solution
    int solve(std::string &solution);

private:
    // Problem parameters
    int jugACapacity, jugBCapacity, goalAmount;
    int costFillA, costFillB, costEmptyA, costEmptyB, costPourAB, costPourBA;

    // Internal struct representing a state of the jugs
    struct State {
        int amountA;    // Current amount in jug A
        int amountB;    // Current amount in jug B
        int cost;       // Accumulated cost to reach this state
        std::string path;    // Sequence of operations to reach this state

        // Used by the priority queue to compare total cost
        bool operator>(const State& other) const {
            return cost > other.cost;
        }
    };

    // Checks whether the input parameters are within the valid constraints
    bool isValidInput() const;
};

#endif
