#include "Jug.h"
#include <queue>
#include <set>
#include <tuple>
#include <climits>
#include <algorithm>  // for std::min

// Constructor: Initializes all member variables with the input parameters
Jug::Jug(int jugACap, int jugBCap, int goal, int costFillA, int costFillB,
         int costEmptyA, int costEmptyB, int costPourAB, int costPourBA) {
    this->jugACapacity = jugACap;
    this->jugBCapacity = jugBCap;
    this->goalAmount = goal;
    this->costFillA = costFillA;
    this->costFillB = costFillB;
    this->costEmptyA = costEmptyA;
    this->costEmptyB = costEmptyB;
    this->costPourAB = costPourAB;
    this->costPourBA = costPourBA;
}

// Destructor
Jug::~Jug() {
    // No cleanup required
}

// Validates the constructor input values against problem constraints
bool Jug::isValidInput() const {
    return jugACapacity > 0 && jugBCapacity > 0 && jugACapacity <= jugBCapacity &&
           goalAmount <= jugBCapacity && goalAmount >= 0 &&
           costFillA > 0 && costFillB > 0 && costEmptyA > 0 && costEmptyB > 0 &&
           costPourAB > 0 && costPourBA > 0 && jugBCapacity <= 1000;
}

// Solves the jug problem using Dijkstra's algorithm to find the cheapest sequence
int Jug::solve(std::string &solution) {
    if (!isValidInput()) {
        solution = "";
        return -1;
    }

    using JugState = std::tuple<int, int>;  // Represents a state as (amountA, amountB)
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    std::set<JugState> visited;

    // Start from the initial state (0, 0)
    pq.push({0, 0, 0, ""});

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int amountA = current.amountA;
        int amountB = current.amountB;

        // Skip already visited states
        if (visited.count({amountA, amountB})) continue;
        visited.insert({amountA, amountB});

        // Check if goal state is reached: jug A is empty and jug B has the goal amount
        if (amountA == 0 && amountB == goalAmount) {
            solution = current.path + "success " + std::to_string(current.cost);
            return 1;
        }

        // Generate all valid next states and push them into the priority queue

        // Fill Jug A
        pq.push({jugACapacity, amountB, current.cost + costFillA, current.path + "fill A\n"});

        // Fill Jug B
        pq.push({amountA, jugBCapacity, current.cost + costFillB, current.path + "fill B\n"});

        // Empty Jug A
        pq.push({0, amountB, current.cost + costEmptyA, current.path + "empty A\n"});

        // Empty Jug B
        pq.push({amountA, 0, current.cost + costEmptyB, current.path + "empty B\n"});

        // Pour Jug A to Jug B
        int pourAB = std::min(amountA, jugBCapacity - amountB);
        pq.push({amountA - pourAB, amountB + pourAB, current.cost + costPourAB, current.path + "pour A B\n"});

        // Pour Jug B to Jug A
        int pourBA = std::min(amountB, jugACapacity - amountA);
        pq.push({amountA + pourBA, amountB - pourBA, current.cost + costPourBA, current.path + "pour B A\n"});
    }

    // If no solution is found
    solution = "";
    return 0;
}
